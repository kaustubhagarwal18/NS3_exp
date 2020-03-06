/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2007 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mathieu Lacage <mathieu.lacage@cutebugs.net>
 */

#include <iostream>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"

using namespace ns3;

static void
GenerateTraffic (Ptr<Socket> socket, uint32_t size)                                                   // size is total number of bytes to be sent
{
  std::cout << "at=" << Simulator::Now ().GetSeconds () << "s, tx bytes=" << size << std::endl;        // at this time how many bytes
  socket->Send (Create<Packet> (size));                                    // Send data (or dummy data) to the remote host after creating the packet
  if (size > 0)
    {
      Simulator::Schedule (Seconds (0.5), &GenerateTraffic, socket, size - 50);   // schedule the simulator to run every 0.5 seconds,function to run, variables  
    }
  else
    {
      socket->Close ();
    }
}

static void
SocketPrinter (Ptr<Socket> socket)
{
  Ptr<Packet> packet;                                        // create a pointer for packet
  while ((packet = socket->Recv ()))                         // put it equal to the packet received at the socket          
    { 
      std::cout << "at=" << Simulator::Now ().GetSeconds () << "s, rx bytes=" << packet->GetSize () << std::endl;   // print received bytes
    }
}

static void
PrintTraffic (Ptr<Socket> socket)                                           // socket is sink 
{
  socket->SetRecvCallback (MakeCallback (&SocketPrinter));                  // make callback to print packets at the sink node
  
}

void
RunSimulation (void)
{
  NodeContainer c;
  c.Create (1);

  InternetStackHelper internet;
  internet.Install (c);

  // Look for UDP socket
  TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");  // tid -> ns3::UdpSocketFactory
  // create UDP socket
  Ptr<Socket> sink = Socket::CreateSocket (c.Get (0), tid);     // sink -> memory address for the socket
  
  InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);   // get any socket address
  
  sink->Bind (local);             // bind the socket to the address? 
  
  Ptr<Socket> source = Socket::CreateSocket (c.Get (0), tid);            // create another socket(for udp traffic)
  InetSocketAddress remote = InetSocketAddress (Ipv4Address::GetLoopback (), 80);  // get any address for the socket
  source->Connect (remote);                                            // connect to socket

  GenerateTraffic (source, 500);                        // Go to the function call
  PrintTraffic (sink);


  Simulator::Run ();

  Simulator::Destroy ();
}

int main (int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);
  
  RunSimulation ();

  return 0;
}
