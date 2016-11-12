#include <xinu.h>

#define ICMP_HEADER_LEN 4

syscall icmpSend(struct ethergram *pkt, uchar type, uchar code, uint datalen,struct netaddr *src, struct netaddr *dst) {
  struct ipgram *ip = NULL; //need the payload of ipgram to set as icmp
  struct ethergram *egram = NULL;
  uchar *buf;
  
  
  ip = pkt->data;
  
  ip->ver_ihl = (uchar)(IPv4_VERSION << 4);
  ip->ver_ihl += IPv4_HDR_LEN; //may need IPv4_MAX_HDRLEN
  ip->tos = IPv4_TOS_ROUTINE; //service type
  ip->len = IPv4_HDR_LEN; // + data length
  ip->id = 0;
  ip->flags_froff = 0;
  ip->ttl = IPv4_TTL;
  ip->proto = IPv4_PROTO_ICMP;
  if (NULL == src->type) {
    memcpy(ip->src, pkt->src, IPv4_ADDR_LEN);
  } else {
    memcpy(ip->src, src->addr, IPv4_ADDR_LEN);
  }
  memcpy(ip->dst, dst->addr, IPv4_ADDR_LEN);
  
 // ip->chksum = 0;
 // ip->chksum = checksum((uchar *)ip, IPv4_HDR_LEN);
  
  //write(ETH0, buf, PKTSZ)
  
  struct icmpPkt {
    uchar type;
    uchar code;
    ushort chksum;
    int data;
  };
  
  struct icmpPkt *icmp = NULL;
  icmp->type = type;
  icmp->code = code;
  icmp->chksum = 0;
  icmp->chksum = netChksum((uchar *)icmp, datalen + ICMP_HEADER_LEN);
  
  ip->opts = icmp;
  
  
  //send packet with number in it, have the other machine send back the number, right before you send the packet, right after you receive the response packet, record the time and subtract the two
  
  
  if (NULL == pkt) {
    return SYSERR;
  }
  
  
  
  
  
}
