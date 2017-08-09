/***************************************************************************
 * ncrack_mongodb.cc -- ncrack module for the MongoDB protocol                 *
 * Coded by edeirme                                                        *
 *                                                                         *
 ***********************IMPORTANT NMAP LICENSE TERMS************************
 *                                                                         *
 * The Nmap Security Scanner is (C) 1996-2016 Insecure.Com LLC. Nmap is    *
 * also a registered trademark of Insecure.Com LLC.  This program is free  *
 * software; you may redistribute and/or modify it under the terms of the  *
 * GNU General Public License as published by the Free Software            *
 * Foundation; Version 2 ("GPL"), BUT ONLY WITH ALL OF THE CLARIFICATIONS  *
 * AND EXCEPTIONS DESCRIBED HEREIN.  This guarantees your right to use,    *
 * modify, and redistribute this software under certain conditions.  If    *
 * you wish to embed Nmap technology into proprietary software, we sell    *
 * alternative licenses (contact sales@nmap.com).  Dozens of software      *
 * vendors already license Nmap technology such as host discovery, port    *
 * scanning, OS detection, version detection, and the Nmap Scripting       *
 * Engine.                                                                 *
 *                                                                         *
 * Note that the GPL places important restrictions on "derivative works",  *
 * yet it does not provide a detailed definition of that term.  To avoid   *
 * misunderstandings, we interpret that term as broadly as copyright law   *
 * allows.  For example, we consider an application to constitute a        *
 * derivative work for the purpose of this license if it does any of the   *
 * following with any software or content covered by this license          *
 * ("Covered Software"):                                                   *
 *                                                                         *
 * o Integrates source code from Covered Software.                         *
 *                                                                         *
 * o Reads or includes copyrighted data files, such as Nmap's nmap-os-db   *
 * or nmap-service-probes.                                                 *
 *                                                                         *
 * o Is designed specifically to execute Covered Software and parse the    *
 * results (as opposed to typical shell or execution-menu apps, which will *
 * execute anything you tell them to).                                     *
 *                                                                         *
 * o Includes Covered Software in a proprietary executable installer.  The *
 * installers produced by InstallShield are an example of this.  Including *
 * Nmap with other software in compressed or archival form does not        *
 * trigger this provision, provided appropriate open source decompression  *
 * or de-archiving software is widely available for no charge.  For the    *
 * purposes of this license, an installer is considered to include Covered *
 * Software even if it actually retrieves a copy of Covered Software from  *
 * another source during runtime (such as by downloading it from the       *
 * Internet).                                                              *
 *                                                                         *
 * o Links (statically or dynamically) to a library which does any of the  *
 * above.                                                                  *
 *                                                                         *
 * o Executes a helper program, module, or script to do any of the above.  *
 *                                                                         *
 * This list is not exclusive, but is meant to clarify our interpretation  *
 * of derived works with some common examples.  Other people may interpret *
 * the plain GPL differently, so we consider this a special exception to   *
 * the GPL that we apply to Covered Software.  Works which meet any of     *
 * these conditions must conform to all of the terms of this license,      *
 * particularly including the GPL Section 3 requirements of providing      *
 * source code and allowing free redistribution of the work as a whole.    *
 *                                                                         *
 * As another special exception to the GPL terms, Insecure.Com LLC grants  *
 * permission to link the code of this program with any version of the     *
 * OpenSSL library which is distributed under a license identical to that  *
 * listed in the included docs/licenses/OpenSSL.txt file, and distribute   *
 * linked combinations including the two.                                  *
 *                                                                         *
 * Any redistribution of Covered Software, including any derived works,    *
 * must obey and carry forward all of the terms of this license, including *
 * obeying all GPL rules and restrictions.  For example, source code of    *
 * the whole work must be provided and free redistribution must be         *
 * allowed.  All GPL references to "this License", are to be treated as    *
 * including the terms and conditions of this license text as well.        *
 *                                                                         *
 * Because this license imposes special exceptions to the GPL, Covered     *
 * Work may not be combined (even as part of a larger work) with plain GPL *
 * software.  The terms, conditions, and exceptions of this license must   *
 * be included as well.  This license is incompatible with some other open *
 * source licenses as well.  In some cases we can relicense portions of    *
 * Nmap or grant special permissions to use it in other open source        *
 * software.  Please contact fyodor@nmap.org with any such requests.       *
 * Similarly, we don't incorporate incompatible open source software into  *
 * Covered Software without special permission from the copyright holders. *
 *                                                                         *
 * If you have any questions about the licensing restrictions on using     *
 * Nmap in other works, are happy to help.  As mentioned above, we also    *
 * offer alternative license to integrate Nmap into proprietary            *
 * applications and appliances.  These contracts have been sold to dozens  *
 * of software vendors, and generally include a perpetual license as well  *
 * as providing for priority support and updates.  They also fund the      *
 * continued development of Nmap.  Please email sales@nmap.com for further *
 * information.                                                            *
 *                                                                         *
 * If you have received a written license agreement or contract for        *
 * Covered Software stating terms other than these, you may choose to use  *
 * and redistribute Covered Software under those terms instead of these.   *
 *                                                                         *
 * Source is provided to this software because we believe users have a     *
 * right to know exactly what a program is going to do before they run it. *
 * This also allows you to audit the software for security holes.          *
 *                                                                         *
 * Source code also allows you to port Nmap to new platforms, fix bugs,    *
 * and add new features.  You are highly encouraged to send your changes   *
 * to the dev@nmap.org mailing list for possible incorporation into the    *
 * main distribution.  By sending these changes to Fyodor or one of the    *
 * Insecure.Org development mailing lists, or checking them into the Nmap  *
 * source code repository, it is understood (unless you specify otherwise) *
 * that you are offering the Nmap Project (Insecure.Com LLC) the           *
 * unlimited, non-exclusive right to reuse, modify, and relicense the      *
 * code.  Nmap will always be available Open Source, but this is important *
 * because the inability to relicense code has caused devastating problems *
 * for other Free Software projects (such as KDE and NASM).  We also       *
 * occasionally relicense the code to third parties as discussed above.    *
 * If you wish to specify special license conditions of your               *
 * contributions, just say so when you send them.                          *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the Nmap      *
 * license file for more details (it's in a COPYING file included with     *
 * Nmap, and also available from https://svn.nmap.org/nmap/COPYING)        *
 *                                                                         *
 ***************************************************************************/


#include "ncrack.h"
#include "nsock.h"
#include "NcrackOps.h"
#include "Service.h"
#include "modules.h"

#define MONGODB_TIMEOUT 10000
#define LONGQUARTET(x) ((x) & 0xff), (((x) >> 8) & 0xff), \
  (((x) >> 16) & 0xff), (((x) >> 24) & 0xff)

extern void ncrack_read_handler(nsock_pool nsp, nsock_event nse, void *mydata);
extern void ncrack_write_handler(nsock_pool nsp, nsock_event nse, void *mydata);
extern void ncrack_module_end(nsock_pool nsp, void *mydata);
static int mongodb_loop_read(nsock_pool nsp, Connection *con);

static void rand_str(char *dest, size_t length);

enum states { MONGODB_INIT, MONGODB_RECEIVE, MONGODB_FINI };

static int
mongodb_loop_read(nsock_pool nsp, Connection *con)
{
  if (con->inbuf == NULL) {
    nsock_read(nsp, con->niod, ncrack_read_handler, MSSQL_TIMEOUT, con);
    return -1;
  }
  return 0;
}

void
ncrack_mongodb(nsock_pool nsp, Connection *con)
{
  nsock_iod nsi = con->niod;
  unsigned char len_login, len_pass;
  int tmplen;
  char * tmp;
  char * payload;
  char * b64_cn; /* client nonce */
  int pklen;
  char *start, *end;
  size_t i;

  switch (con->state)
  {
    case MONGODB_INIT:
      /* List DB step */

      if (con->outbuf)
        delete con->outbuf;
      con->outbuf = new Buf();    

      tmplen = 4 + 4  /* mesage length + request ID*/
         + 4 + 4 + 4  /* response to + opcode + queryflags */
         + strlen(con->database) + strlen(".$cmd") + 1 /* full collection name + null byte */
         + 4 + 4 /* number to skip, number to return */
         + 4 /* query length */
         + 1 + strlen("listDatabases") + 1 + 4 + 4 /* element list database length */
         + 1 /* null byte */
         ;
      tmp = (char *)safe_malloc(tmplen + 1); 
      
      char *full_collection_name;

      full_collection_name = (char *)safe_malloc(strlen(con->database) + strlen(".$cmd") + 1);

      sprintf(full_collection_name, "%s%s", con->database, ".$cmd");

      snprintf((char *)tmp, tmplen,
         "%c%c%c%c" /* message length */ 
         "%c%c%c%c" /* request ID, might have to be dynamic */
         "\xff\xff\xff\xff" /* response to */
         "\xd4\x07%c%c" /* OpCode: We use query 2004 */              
         "%c%c%c%c" /* Query Flags */
         "%s" /* Full Collection Name */
        /* might need a null byte here */
         "%c%c%c%c" /* Number to Skip (0) */
         "\xff\xff\xff\xff" /* Number to return (-1) */
         "\x1c%c%c%c" /* query length, fixed length (28) */
         "\x01" /* query type (Double 0x01) */
         "%s" /* element (listDatabases) */              
        /* might need a null byte here */
         "%c%c%c%c" /* element value (1) */
         "%c%c\xf0\x3f" /* element value (1) cnt. */
         "%c", /* end of packet null byte */
         0x00,0x00,0x30,0x3a,
         0x00,0x00,
         0x00,0x00,0x00,0x00,
         full_collection_name,
         0x00,0x00,0x00,0x00, /* Num to skip */
         0x00,0x00,0x00, /* query length */
         "listDatabases",
         0x00,0x00,0x00,0x00,
         0x00,0x00,
         0x00
         );     

      con->outbuf->append(tmp, tmplen);
      free(tmp);
      free(full_collection_name);

      nsock_write(nsp, nsi, ncrack_write_handler, MSSQL_TIMEOUT, con,
        (const char *)con->outbuf->get_dataptr(), con->outbuf->get_len());

      con->state = MONGODB_RECEIVE;
      break;

    case MONGODB_RECEIVE:
      if (memsearch((const char *)con->inbuf->get_dataptr(),
            "errmsg", con->inbuf->get_len()) 
          || memsearch((const char *)con->inbuf->get_dataptr(),
            "not authorized", con->inbuf->get_len())) {
        con->state = MONGO_STEP1;
      } else {
        /* In this case the mongo database does not have authorization.
        * The module terminates with success. 
        */
        con->auth_success = true;
        return ncrack_module_end(nsp, con);
      }
      break;

    case MONGO_STEP1:
      if (con->outbuf)
        delete con->outbuf;
      con->outbuf = new Buf();    

      /* Generate client nonce. The nonce is usually 10-13 random bytes.
      * These bytes are base64 encoded.
      */
      tmp = (char *)safe_malloc(12 + 1);
      rand_str(tmp, 12);
      b64_cn = (char *)safe_malloc(BASE64_LENGTH(12) + 1);
      base64_encode(tmp, 12, b64_cn);
      free(tmp);

      tmplen = 4 + 4  /* mesage length + request ID*/
         + 4 + 4 + 4  /* response to + opcode + queryflags */
         + strlen(con->database) + strlen(".$cmd") + 1 /* full collection name + null byte */
         + 4 + 4 /* number to skip, number to return */
         + 4 /* query length */

         + 1 + strlen("saslStart") + 1 + 4  /* element saslStart length */
         + 1 + strlen("mechanism") + 1 + 4 + strlen("SCRAM-SHA-1") + 1 /* element SCRAM-SHA-1 length */
         + 1 + strlen("payload") + 1 + 4 + strlen(payload) /* element payload length */
         + 1 + strlen("autoAuthorize") + 1 + 4  /* element autoAuthorize length */

         + 1 /* null byte */
         ;
      tmp = (char *)safe_malloc(tmplen + 1);

      char *full_collection_name;

      full_collection_name = (char *)safe_malloc(strlen(con->database) + 6 + 1);

      sprintf(full_collection_name, "%s%s", con->database, ".$cmd");

      /* Allocate 12 bytes for the client nonce, the length of the username
      * and 8 bytes for the following sequence "n,,n=,r="
      */
      payload = (char *)safe_malloc(12 + strlen(con->user) + 8);
      snprintf(payload, "n,,n=%s,r=%s", con->user, b64_cn);

      snprintf((char *)tmp, tmplen,
         "%c%c%c%c" /* message length */ 
         "%c%c%c%c" /* request ID, might have to be dynamic */
         "\xff\xff\xff\xff" /* response to */
         "\xd4\x07%c%c" /* OpCode: We use query 2004 */              
         "%c%c%c%c" /* Query Flags */
         "%s" /* Full Collection Name */
        /* might need a null byte here */
         "%c%c%c%c" /* Number to Skip (0) */
         "\xff\xff\xff\xff" /* Number to return (-1) */
         "%c%c%c%c" /* query length, dynamic */

         "\x10" /* query type (Int32 0x10) */
         "%s" /* element (saslStart) */              
         "%c" /* element null byte */
         "\x01%c%c%c" /* element value (1) */

         "\x02" /* query type (String 0x02) */
         "%s" /* element (mechanism) */              
         "%c" /* element null byte */
         "\x0c%c%c%c" /* element value length (12) */
         "%s" /* element value (SCRAM-SHA-1) */
         "%c" /* element value null byte */

         "\x05" /* query type (Binary 0x05) */
         "%s" /* element (payload) */              
         "%c" /* element null byte */
         "%c%c%c%c" /* element value length (dynamic) */
         "%s" /* element value */

         "\x10" /* query type (Int32 0x10) */
         "%s" /* element (autoAuthorize) */              
         "%c" /* element null byte */
         "\x01%c%c%c" /* element value (1) */

         "%c", /* end of packet null byte */

         LONGQUARTET(tmplen),
         0x00,0x00,0x30,0x3a,
         0x00,0x00,
         0x00,0x00,0x00,0x00,
         full_collection_name,
         0x00,0x00,0x00,0x00, /* Num to skip */
         0x00,0x00,0x00,0x00, /* query length fix me   */
         "saslStart", 0x00,
         0x00,0x00,0x00,
         "mechanism", 0x00,
         0x00,0x00,0x00,
         "SCRAM-SHA-1", 0x00,

         "binary",0x00,
         LONGQUARTET(strlen(payload)),
         payload,

         "autoAuthorize", 0x00,
         0x00,0x00,0x00,

         0x00
         );     

      con->outbuf->append(tmp, tmplen);
      free(full_collection_name);
      free(payload);
      free(b64_cn);
      free(tmp);

      nsock_write(nsp, nsi, ncrack_write_handler, MSSQL_TIMEOUT, con,
        (const char *)con->outbuf->get_dataptr(), con->outbuf->get_len());
      break;

    case MONGODB_FINI:

      if (mssql_loop_read(nsp, con) < 0)
        break;
      /* We search for the string 'payload' in the server's response.
      * We extract that value and proceed with step 3.
      * Probably we should check if the bytes 12-16 are 01000000 (Reply opcode).
      */
      if (!memsearch((const char *)con->inbuf->get_dataptr(),
            "payload", con->inbuf->get_len())) {
        /* Abort.
        */
      }

      /* Search for value i (i=) for iterations, s (s=) for salt, 
      * and r (r=) for server nonce. The delimiter is comma (,).
      */
      /* The 'r' variable should begin with the nonce we sent above.
      * ClientNone + ServerNonce. If not we should abort.
      */
      con->state = MONGODB_INIT;
      return ncrack_module_end(nsp, con);

    case MONGODB_CR_START:
      if (con->outbuf)
        delete con->outbuf;
      con->outbuf = new Buf();    

      tmplen = 4 + 4  /* mesage length + request ID*/
         + 4 + 4 + 4  /* response to + opcode + queryflags */
         + strlen(con->database) + strlen(".$cmd") + 1 /* full collection name + null byte */
         + 4 + 4 /* number to skip, number to return */
         + 4 /* query length */

         + 1 + strlen("getnonce") + 1 + 4 + 4 /* element getnonce length */

         + 1 /* null byte */
         ;
      tmp = (char *)safe_malloc(tmplen + 1);

      char *full_collection_name;

      full_collection_name = (char *)safe_malloc(strlen(con->database) + 6 + 1);

      sprintf(full_collection_name, "%s%s", con->database, ".$cmd");


      snprintf((char *)tmp, tmplen,
         "%c%c%c%c" /* message length */ 
         "%c%c%c%c" /* request ID, might have to be dynamic */
         "\xff\xff\xff\xff" /* response to */
         "\xd4\x07%c%c" /* OpCode: We use query 2004 */              
         "%c%c%c%c" /* Query Flags */
         "%s" /* Full Collection Name */
        /* might need a null byte here */
         "%c%c%c%c" /* Number to Skip (0) */
         "\xff\xff\xff\xff" /* Number to return (-1) */
         "\x17%c%c%c" /* query length, fixed 23 */

         "\x01" /* query type (Double 0x01) */
         "%s" /* element (getnonce) */              
         "%c" /* element null byte */
         "%c%c%c%c" /* element value (1) */
         "%c%c\xf0\x3f" /* element value (1) cnt. */

         "%c", /* end of packet null byte */

         LONGQUARTET(tmplen),
         0x00,0x00,0x30,0x3a,
         0x00,0x00,
         0x00,0x00,0x00,0x00,
         full_collection_name,
         0x00,0x00,0x00,0x00, /* Num to skip */
         0x00,0x00,0x00, 
         "getnonce", 0x00,
         0x00,0x00,0x00,0x00,
         0x00,0x00,        

         0x00
         );     

      con->outbuf->append(tmp, tmplen);
      free(full_collection_name);
      free(tmp);

      nsock_write(nsp, nsi, ncrack_write_handler, MSSQL_TIMEOUT, con,
        (const char *)con->outbuf->get_dataptr(), con->outbuf->get_len());
      break;

    case MONGODB_CR_NONCE:
      if (!memsearch((const char *)con->inbuf->get_dataptr(),
            "nonce", con->inbuf->get_len())) {
        /* Abort.
        */
      }
    /* There is a nonce element. In CR mode the nonce has a length attribute.
    * Read the length and then read the nonce. The length is 4 bytes after
    * the 'nonce\0' string.
    */
      return ncrack_module_end(nsp, con);    

    case MONGODB_CR_FINI:
      return ncrack_module_end(nsp, con);
  }
}

static void 
rand_str(char *dest, size_t length) 
{
    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (length-- > 0) {
        size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}