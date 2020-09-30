package org.bits.distributed.assignment;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

import org.bits.distributed.assignment.util.MapUtil;

public class LogicalClkMain {

	static int _nodes;
	static volatile boolean isShutDown = false;
	static Map<String,Integer> messageMap = new ConcurrentHashMap<String,Integer>();
	
	public static void main(String argv[])
	{
		if (argv.length != 2)
		{
			System.out.println("Usage: script Number_no_nodes time_to_run ");
			System.exit(0);
		}
		try
		{
			_nodes = Integer.parseInt(argv[0]);
			Thread[] nodesArray = new Thread[_nodes];
			for (int i = 0; i < _nodes; i++)
			{
				LamportNode newNode = new LamportNode(8000 + i);
				nodesArray[i] = new Thread(newNode);
				nodesArray[i].setName("Node " + new Integer(i).toString());
				System.out.println("Node " + new Integer(i).toString() + " created. Listening at " 
						+ new Integer(8000 + i).toString());
			}
			for (int i = 0 ; i < _nodes ; i ++)
			{
				nodesArray[i].start();
			}
			
			Thread.sleep(Integer.parseInt(argv[1]) * 60 * 1000 );
			isShutDown = true;
			for (Thread thread : nodesArray)
			{
				  thread.join();
			}
			Map<String,Integer> sortedEvents = MapUtil.sortByValue(messageMap);
			System.out.println("Ordering of generated events are as -");
			System.out.println("e[Node][Event]: ClockValue");
			int lastValue = 1;
			for (Map.Entry<String, Integer> entry : sortedEvents.entrySet())
			{
				if(entry.getValue() != lastValue)
				{
					System.out.println("Happend before");
					lastValue = entry.getValue();
				}
			    System.out.println(entry.getKey() + ":" + entry.getValue());
			}
			System.exit(0);
		}
		catch(NumberFormatException e)
		{
			
		}
		catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
}
