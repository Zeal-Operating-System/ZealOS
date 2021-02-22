
#include "../DNS"
#include "../NetHandlerTask"

/*
"Manually setting DNS Resolver IP.\n";

CIPV4Address *addr = CAlloc(sizeof(CIPV4Address));
PresentationToNetwork(AF_INET, "192.168.1.254", addr);

DNSResolverIPV4Set(addr->address);
*/
"Trying Host() at \"google.com\".\n";
Host("google.com");

Free(addr);