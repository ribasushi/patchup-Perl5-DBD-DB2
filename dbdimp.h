/*
   engn/perldb2/dbdimp.h, engn_perldb2, db2_v81, 1.6 00/09/06 15:58:14

   Copyright (c) 1995,1996,1997,1998,1999,2000 International Business Machines Corp.
*/

/* these are (almost) random values ! */
#define MAX_COL_NAME_LEN 128
#define MAX_BIND_VARS   99


typedef struct imp_fbh_st imp_fbh_t;

struct imp_drh_st {
  dbih_drc_t com;                     /* MUST be first element in structure   */
  SQLHENV henv;
  int     connects;
};

/* Define dbh implementor data structure */
struct imp_dbh_st {
  dbih_dbc_t com;                     /* MUST be first element in structure   */
  SQLHENV henv;
  SQLHDBC hdbc;
};


/* Define sth implementor data structure */
struct imp_sth_st {
  dbih_stc_t  com;                    /* MUST be first element in structure   */
  SQLHENV     henv;
  SQLHDBC     hdbc;
  SQLHSTMT    phstmt;

  /* Input Details    */
  SQLCHAR     *statement;             /* sql (see sth_scan)                   */
  HV          *bind_names;

  /* Output Details   */
  SQLINTEGER  done_desc;              /* have we described this sth yet ?     */
  imp_fbh_t   *fbh;                   /* array of imp_fbh_t structs           */
  SQLCHAR     *fbh_cbuf;              /* memory for all field names           */
  SQLINTEGER  RowCount;               /* Rows affected by insert, update,     */
                                      /* delete (unreliable for SELECT)       */
  int         bHasInput;              /* Has at least one input parameter     */
                                      /* (by reference)                       */
  int         bHasOutput;             /* Has at least one output parameter    */
};
#define IMP_STH_EXECUTING       0x0001


struct imp_fbh_st {     /* field buffer */
  imp_sth_t *imp_sth; /* 'parent' statement */

  /* description of the field */
  SQLSMALLINT dbtype;
  SQLCHAR    *cbuf;           /* ptr to name of select-list item */
  SQLSMALLINT cbufl;          /* length of select-list item name */
  SQLINTEGER  dsize;          /* max display size if field is a SQLCHAR */
  SQLUINTEGER prec;
  SQLSMALLINT scale;
  SQLSMALLINT nullok;

  /* Our storage space for the field data as it's fetched */
  SQLSMALLINT ftype;          /* external datatype we wish to get             */
  short       indp;           /* null/trunc indicator variable                */
  void       *buffer;         /* data buffer (poSQLINTEGERs to sv data)       */
  SQLINTEGER  bufferSize;     /* length of data buffer                        */
  SQLINTEGER  rlen;           /* length of returned data                      */
};


typedef struct phs_st phs_t;    /* scalar placeholder */

struct phs_st { /* scalar placeholder */
  SV          *sv;                  /* the variable reference for bind_inout  */
  void        *buffer;              /* input and output buffer                */
  int          bufferSize;          /* size of buffer                         */
  SQLUSMALLINT paramType;           /* INPUT, OUTPUT or INPUT_OUTPUT          */
  SQLINTEGER   indp;                /* null indicator or length indicator     */
  int          bDescribed;          /* already described this parameter       */
  int          bDescribeOK;         /* describe was successful                */
  SQLSMALLINT  descSQLType;
  SQLSMALLINT  descDecimalDigits;
  SQLUINTEGER  descColumnSize;
};

SQLCHAR sql_state[6];

#define dbd_init            db2_init
#define dbd_db_login        db2_db_login
#define dbd_db_do           db2_db_do
#define dbd_db_commit       db2_db_commit
#define dbd_db_rollback     db2_db_rollback
#define dbd_db_disconnect   db2_db_disconnect
#define dbd_db_destroy      db2_db_destroy
#define dbd_db_STORE_attrib db2_db_STORE_attrib
#define dbd_db_FETCH_attrib db2_db_FETCH_attrib
#define dbd_db_tables       db2_db_tables
#define dbd_st_table_info   db2_st_table_info
#define dbd_st_prepare      db2_st_prepare
#define dbd_st_rows         db2_st_rows
#define dbd_st_execute      db2_st_execute
#define dbd_st_fetch        db2_st_fetch
#define dbd_st_finish       db2_st_finish
#define dbd_st_destroy      db2_st_destroy
#define dbd_st_blob_read    db2_st_blob_read
#define dbd_st_STORE_attrib db2_st_STORE_attrib
#define dbd_st_FETCH_attrib db2_st_FETCH_attrib
#define dbd_describe        db2_describe
#define dbd_bind_ph         db2_bind_ph

/* end */
