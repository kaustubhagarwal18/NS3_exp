# NS3_exp

Basic traffic shaping experiemnt at the router end. 

Keep current script in the scratch folder.
./waf to build
Commands to run ~/Desktop/ns-allinone-3.30/ns-3.30$ ./waf --run scratch/first

Logging - 
NS_LOG_COMPONENT_DEFINE ("RealtimeUdpEchoExample");  // define the logging component
NS_LOG=RealtimeUdpEchoExample=info                // run in terminal to enable the logging component

./waf --run traffic-control > traffic-control.dat 2>&1             // save it to dat file

Debugging comment - NS_LOG_UNCOND ("Test");  // logging variable


NS_LOG="SimpleGlobalRoutingExample"=info ./waf --run scratch/simple-global-routing

tcpdump -nn -tt -r simple-global-routing-0-1.pcap



# On-OFF Application

  OnOffHelper onoff2 ("ns3::UdpSocketFactory",
                      InetSocketAddress (i1i6.GetAddress (1), port));                               // Address of node which will receive traffic
  onoff2.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
  onoff2.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
  onoff2.SetAttribute ("DataRate", StringValue ("2kbps"));
  onoff2.SetAttribute ("PacketSize", UintegerValue (50));

  ApplicationContainer apps2 = onoff2.Install (c.Get (1));          // Address of node which will send traffic
    apps2.Start (Seconds (11.0));
  apps2.Stop (Seconds (16.0));

## Netanim stuff

#include "ns3/netanim-module.h" -- include header

  AnimationInterface anim ("first_animation.xml");     // xml file for NetAnim --- stored in ns3.30 folder
  anim.SetConstantPosition(nodes.Get(0), 1.0,2.0);
  anim.SetConstantPosition(nodes.Get(1), 20.0,30.0);

  Simulator::Run ();
  Simulator::Destroy ();
  
Run - ~ns-allinone-3.30/netanim$ ./NetAnim         -- for Netanim

Base structure -  
Create node 
install associate ethernet device, channel(wireless,p2p,csma) , attribues(datarate,framerate)
install ip protocols
install base ip address
install applicaion(ftp,clientserver application on the nodes)
