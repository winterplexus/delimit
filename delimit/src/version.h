/*
**  @(#)version.h
**
**  delimit - version information
**  -----------------------------
**
**  copyright (c) 1993-2025 Code Construct Systems (CCS)
*/
#ifndef __VERSION_H
#define __VERSION_H

/*
** Check if version product and string are defined in another include file
*/
#ifdef  _VERSION_PRODUCT
#error  _VERSION_PRODUCT is defined in another include file
#endif
#ifdef  _VERSION_RELEASE
#error  _VERSION_RELEASE is defined in another include file
#endif

/*
** Define version product and string
*/
#define _VERSION_PRODUCT "delimit"
#define _VERSION_RELEASE "delimit 9.8.0 release 1"

#endif /* __VERSION_H */
