# NS3_exp

Basic traffic shaping experiemnt at the router end. 

Keep current script in the scratch folder.
./waf to build
Commands to run ~/Desktop/ns-allinone-3.30/ns-3.30$ ./waf --run scratch/first

Logging - 
NS_LOG_COMPONENT_DEFINE ("RealtimeUdpEchoExample");  // define the logging component
NS_LOG=RealtimeUdpEchoExample=info                // run in terminal to enable the logging component

./waf --run traffic-control > traffic-control.dat 2>&1             // save it to dat file

Debugging commeent - NS_LOG_UNCOND ("Test");  // logging variable

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
