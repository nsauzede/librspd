// SPDX-License-Identifier: LGPL-2.1-or-later

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "librspd.h"

int xlen = 32;
int
rsp_question(void* user)
{
  void* rsp = *(void**)user;
  char* buf = "S05";
  rsp_send(rsp, buf, strlen(buf));
  return 0;
}

int
rsp_stepi(void* user)
{
  void* rsp = *(void**)user;
  rsp_stopped(rsp);
  return 1;
}

int
rsp_cont(void* user)
{
  void* rsp = *(void**)user;
  rsp_stopped(rsp);
  return 1;
}

int killed = 0;
int
rsp_kill(void* user)
{
  user = user;
  killed = 1;
  return -1;
}

#define LEN64 (560 * 2)
#define LEN32 (312 * 2)
int
rsp_get_regs(void* user)
{
  void* rsp = *(void**)user;
  char buf[LEN64 + 1];
  size_t len = xlen == 64 ? LEN64 : LEN32;
  memset(buf, '0', len);
  rsp_send(rsp, buf, len);
  return 0;
}

int
rsp_read_mem(void* user, size_t addr, size_t len)
{
  void* rsp = *(void**)user;
  char* buf = malloc(len * 2);
  memset(buf, '0' + (int)(addr % 10), len * 2);
  rsp_send(rsp, buf, len * 2);
  free(buf);
  return 0;
}

int
main(int argc, char* argv[])
{
  int debug = 0;
  int arg = 1;
  if (arg < argc) {
    sscanf(argv[arg++], "%d", &debug);
  }
  int port = 1235;
  void* rsp = rsp_init(&(rsp_init_t){
    .user = &rsp,
    .debug = debug,
    .port = port,
    .question = rsp_question,
    .get_regs = rsp_get_regs,
    .read_mem = rsp_read_mem,
    .stepi = rsp_stepi,
    .cont = rsp_cont,
    .kill = rsp_kill,
  });
  if (!rsp) {
    return 1;
  }
  while (!killed) {
    int ret = rsp_execute(rsp);
    if (ret == 0) {
      printf("null ret should not happen ? (killed=%d)\n", killed);
      break;
    }
  }
  rsp_cleanup(rsp);
  return 0;
}
