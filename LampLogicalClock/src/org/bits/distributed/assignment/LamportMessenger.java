package org.bits.distributed.assignment;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

public class LamportMessenger implements Runnable{

	private int port;
	private LamportNode node;
	private ServerSocket messageRecv;
	
	public LamportMessenger( int port, LamportNode node)
	{
		this.port = port;
		this.node = node;
	}
	
	public void init()
	{
		int recvClock;
		String nodeClockValue;
		
		try
		{
			messageRecv = new ServerSocket(port);
			while(!LogicalClkMain.isShutDown)
			{
				try
				{
					Socket connSocket = messageRecv.accept();
					BufferedReader fromNode = new BufferedReader(
							new InputStreamReader(connSocket.getInputStream()));
					nodeClockValue = fromNode.readLine();
					recvClock = Integer.parseInt(nodeClockValue);
					node.updateNodeClock(recvClock);
				}
				catch(NumberFormatException e)
				{
					
				}
			}
				
		}
		catch(IOException io)
		{
			
		}
		
	}
	
	public void sendMessage(int clockvalue, int port)
	{
		String clkString = new String(new Integer(clockvalue).toString());
		try 
		{
			Socket connNodeSocket = new Socket("127.0.0.1",port);
			DataOutputStream toNode = 
					new DataOutputStream(connNodeSocket.getOutputStream());
			toNode.write(clkString.getBytes());
			connNodeSocket.close();
			
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void closeConnection()
	{
			try {
				messageRecv.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			catch(Exception e )
			{
				
			}
	}

	@Override
	public void run() {
		init();
	}
	
}
