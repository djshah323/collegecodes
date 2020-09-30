package org.bits.distributed.assignment;

import java.util.Random;

import org.bits.distributed.assignment.util.Util;

public class LamportNode implements Runnable {

	private int eventNumber ;
	private int nodeNumber;
	private int nodeclock;
	private Object updateLock = new Object();
	private LamportMessenger _LMessenger;
	private Random  rand = new Random();
	
	public LamportNode(int port)
	{
		eventNumber = 0;
		nodeNumber = port - 8000;
		_LMessenger = new LamportMessenger(port, this);
		new Thread(_LMessenger).start();
		nodeclock = 0;
	}
	@Override
	public void run() {

		while(!LogicalClkMain.isShutDown)
		{
			try
			{
				int newInt = rand.nextInt(Integer.MAX_VALUE);
				int mod = newInt % LogicalClkMain._nodes;
				 if(mod != nodeNumber)
				{
					sendNodeClock(8000 + mod);
					eventNumber ++;
					LogicalClkMain.messageMap.put("e" +  "[" + Util.convert(nodeNumber) + "]" + "[" +
							Util.convert(eventNumber) + "]",
							new Integer(nodeclock));
				}
				else 
				{
					updateOwnClock();
					eventNumber ++;
					LogicalClkMain.messageMap.put("e" +  "[" + Util.convert(nodeNumber) + "]" + "[" +
							Util.convert(eventNumber) + "]",
							new Integer(nodeclock));
				}
					
				//pause for 3 mins
				Thread.currentThread().sleep(5000);
			}
			catch(InterruptedException e)
			{
				
			}
			
		}
		
		_LMessenger.closeConnection();

	}

	public void updateNodeClock(int newClockValue)
	{
		synchronized (updateLock) 
		{
			int oldClock = nodeclock;
			if(newClockValue > nodeclock)
				nodeclock = newClockValue;
			nodeclock ++;
			
			System.out.println("Node " + new Integer(nodeNumber).toString() + 
					" Received message. Recv Clock: " + Util.convert(newClockValue) +
					" Own Clock: " + Util.convert(oldClock) +
					" New Clock: " + Util.convert(nodeclock));
		}

	}
	
	public void sendNodeClock(int port)
	{
		int oldclock = nodeclock;
		synchronized (updateLock) 
		{
			nodeclock ++;
			
			System.out.println("Node " + new Integer(nodeNumber).toString() + 
					" Sending message to Node " + Util.convert(port - 8000) +
					" Last clock: " + Util.convert(oldclock) + 
					" New Clock: " + Util.convert(nodeclock));
			
			_LMessenger.sendMessage(nodeclock, port);	
		}
	}
	
	public void updateOwnClock()
	{
		synchronized (updateLock) {
		
			nodeclock ++;
			
			System.out.println("Node " + Util.convert(nodeNumber) + 
					" Takes a local step " +
					" New Clock: " + Util.convert(nodeclock));
		}
	
	}
}
