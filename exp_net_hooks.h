#ifndef EXP_NET_HOOKS_H
#define EXP_NET_HOOKS_H

#include <stdint.h>
#include <stdbool.h>

#ifndef EXP_ENABLE_TRIG
#define EXP_ENABLE_TRIG 0
#endif

#ifndef EXP_HOPS
#define EXP_HOPS 0          /* 0 = không lọc (TN1). 1..4 = TN2 */
#endif

/* Xung relay */
#if EXP_ENABLE_TRIG
extern void exp_trig(uint8_t n);
#define EXP_NET_TRIG(n)         exp_trig(n)
#else
#define EXP_NET_TRIG(n)         ((void)0)
#endif

/* Lọc ingress theo MAC node đứng liền trước */
#if EXP_HOPS > 0
extern bool exp_ingress_allowed(const uint8_t * p_addr);
#define EXP_NET_INGRESS_OK(md)  (((md) == NULL) || \
                                 ((md)->source != NRF_MESH_RX_SOURCE_SCANNER) || \
                                 exp_ingress_allowed((md)->params.scanner.adv_addr.addr))
#else
#define EXP_NET_INGRESS_OK(md)  (true)
#endif

#endif