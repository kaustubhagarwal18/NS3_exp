/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
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
 */

 // 

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;                           

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int main (int argc, char *argv[])
{
  CommandLine cmd;                          // can use this as a cmd argument
  cmd.Parse (argc, argv);
  
  Time::SetResolution (Time::NS); // The resolution is the smallest time value that can be represented (as well as the smallest representable difference between two time values)
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO); //These two lines of code enable debug logging at the INFO level for echo clients and servers.
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO); // This will result in the application printing out messages as packets are sent and received during the simulation.

  NodeContainer nodes;                             // create a object named nodes from class NodeContainer
  nodes.Create (2);                                // Number of nodes

  PointToPointHelper pointToPoint;                 // set a communication channel (pointtopoint in this case)
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));   // A -------------- B (5 Mbps, 2ms)
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer devices;                      
  devices = pointToPoint.Install (nodes);           // install the channel on top of nodes

  InternetStackHelper stack;                        // intstall internet protocol on top of nodes
  stack.Install (nodes);

  Ipv4AddressHelper address;                        // Assign ipv4 addresses
  address.SetBase ("10.1.1.0", "255.255.255.0");    // ip and subnet mask     

  Ipv4InterfaceContainer interfaces = address.Assign (devices);    // assign ip to all devices , client - 1.1 , server(19) - 1.2

  UdpEchoServerHelper echoServer (19);                            // need to make a server for client server model , port is 9

  ApplicationContainer serverApps = echoServer.Install (nodes.Get (1));       // install server on a node 
  serverApps.Start (Seconds (1.0));                                          // Start server
  serverApps.Stop (Seconds (10.0));                                          // Stop server

  UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 19);             // tell client server is at port 19 
  echoClient.SetAttribute ("MaxPackets", UintegerValue (3));                         // number of packets(3)  
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));                   // time between every packet
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));              

  ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));


  AnimationInterface anim ("first_animation.xml");     // xml file for NetAnim
  anim.SetConstantPosition(nodes.Get(0), 1.0,2.0);
  anim.SetConstantPosition(nodes.Get(1), 20.0,30.0);

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
