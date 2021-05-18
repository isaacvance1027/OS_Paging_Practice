/*
 * File: pager-predict.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains a predictive pageit
 *      implmentation.
 */

 #include <limits.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include "simulator.h"


 void pageit(Pentry q[MAXPROCESSES]) {
   int pc;
   int proc;
   int page;
   for (proc = 0; proc < MAXPROCESSES; proc++) {
     if (q[proc].active) {
       int pagesIn[15] = {0};
       pc = q[proc].pc;
       page = pc / PAGESIZE;
       switch (page) {
         case 0:
           pagesIn[0] = 1;
           pagesIn[1] = 1;
           break;
         case 1:
           pagesIn[1] = 1;
           pagesIn[2] = 1;
           break;
         case 2:
           pagesIn[2] = 1;
           pagesIn[3] = 1;
           break;
         case 3:
           pagesIn[0] = 1;
           pagesIn[3] = 1;
           pagesIn[4] = 1;
           pagesIn[10] = 1;
           pagesIn[11] = 1;
           break;
         case 4:
           pagesIn[4] = 1;
           pagesIn[5] = 1;
           pagesIn[11] = 1;
           break;
         case 5:
           pagesIn[5] = 1;
           pagesIn[6] = 1;
           break;
         case 6:
           pagesIn[3] = 1;
           pagesIn[6] = 1;
           pagesIn[7] = 1;
           pagesIn[8] = 1;
           break;
         case 7:
           pagesIn[7] = 1;
           pagesIn[8] = 1;
           break;
         case 8:
           pagesIn[0] = 1;
           pagesIn[8] = 1;
           pagesIn[9] = 1;
           break;
         case 9:
           pagesIn[0] = 1;
           pagesIn[9] = 1;
           pagesIn[10] = 1;
           break;
         case 10:
           pagesIn[0] = 1;
           pagesIn[10] = 1;
           pagesIn[11] = 1;
           pagesIn[12] = 1;
           break;
         case 11:
           pagesIn[0] = 1;
           pagesIn[4] = 1;
           pagesIn[11] = 1;
           pagesIn[12] = 1;
           break;
         case 12:
           pagesIn[0] = 1;
           pagesIn[9] = 1;
           pagesIn[12] = 1;
           pagesIn[13] = 1;
           break;
         case 13:
           pagesIn[0] = 1;
           pagesIn[9] = 1;
           pagesIn[13] = 1;
           pagesIn[14] = 1;
           break;
         case 14:
           pagesIn[0] = 1;
           pagesIn[1] = 1;
           pagesIn[10] = 1;
           pagesIn[11] = 1;
           pagesIn[14] = 1;
           break;
       }
       for (int i = 0; i < 15; i++) {
         if (!pagesIn[i]) {
           pageout(proc, i);
         } else {
           if (!q[proc].pages[i]) {
             pagein(proc, i);
           }
         }
       }
     }
   }
 }
