/*
 * File: pager-lru.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains an lru pageit
 *      implmentation.
 */


 #include <limits.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include "simulator.h"


 void pageit(Pentry q[MAXPROCESSES]) {
   /* This file contains the stub for an LRU pager */
   /* You may need to add/remove/modify any part of this file */
   /* Static vars */
   static int initialized = 0;
   static int tick = 1;  
   static int timestamps[MAXPROCESSES][MAXPROCPAGES];


   int pc;
   int proctmp;
   int pagetmp;
   int oldpage;
   int lru = INT_MAX;

   if (!initialized) {
     for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++) {
       for (pagetmp = 0; pagetmp < MAXPROCPAGES; pagetmp++) {
         timestamps[proctmp][pagetmp] = 0;
       }
     }
     initialized = 1;
   }
   for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++) {
     if (q[proctmp].active) {
       pc = q[proctmp].pc;
       pagetmp = pc / PAGESIZE;
       timestamps[proctmp][pagetmp] = tick;
       if (!q[proctmp].pages[pagetmp]) {
         if (!pagein(proctmp, pagetmp)) {
           for (oldpage = 0; oldpage < q[proctmp].npages; oldpage++) {
             if (timestamps[proctmp][oldpage] < lru &&
                 q[proctmp].pages[oldpage]) {
               lru = timestamps[proctmp][oldpage];
               break;
             }
           }
           pageout(proctmp, oldpage);
         }
       }
     }
     tick++;
   }
 }
