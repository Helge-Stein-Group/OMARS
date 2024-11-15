/* dtrsl.f -- translated by f2c (version of 23 April 1993  18:34:30).
   You must link the resulting object file with the libraries:
    -lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;

/* Triangular Solve  dtrsl() */
/* ---------------- */
/*     solves systems of the form */

/*                   t * x = b */
/*     or */
/*                   trans(t) * x = b */

/*     where t is a triangular matrix of order n. here trans(t) */
/*     denotes the transpose of the matrix t. */

/*     on entry */

/*         t         double precision(ldt,n) */
/*                   t contains the matrix of the system. the zero */
/*                   elements of the matrix are not referenced, and */
/*                   the corresponding elements of the array can be */
/*                   used to store other information. */

/*         ldt       integer */
/*                   ldt is the leading dimension of the array t. */

/*         n         integer */
/*                   n is the order of the system. */

/*         b         double precision(n). */
/*                   b contains the right hand side of the system. */

/*         job       integer */
/*                   job specifies what kind of system is to be solved. */
/*                   if job is */

/*                        00   solve t*x=b, t lower triangular, */
/*                        01   solve t*x=b, t upper triangular, */
/*                        10   solve trans(t)*x=b, t lower triangular, */
/*                        11   solve trans(t)*x=b, t upper triangular. */

/*     on return */

/*         b         b contains the solution, if info .eq. 0. */
/*                   otherwise b is unaltered. */

/*         info      integer */
/*                   info contains zero if the system is nonsingular. */
/*                   otherwise info contains the index of */
/*                   the first zero diagonal element of t. */

/*     linpack. this version dated 08/14/78 . */
/*     g. w. stewart, university of maryland, argonne national lab. */

/*     subroutines and functions */

/*     blas:     daxpy,ddot */
/*     fortran   mod */

/* Subroutine */ int dtrsl_(t, ldt, n, b, job, info)
doublereal *t;
integer *ldt, *n;
doublereal *b;
integer *job, *info;
{
    /* System generated locals */
    integer t_dim1, t_offset, i__1, i__2;

    /* Local variables */
    static integer case_;
    extern doublereal ddot_();
    static doublereal temp;
    static integer j;
    extern /* Subroutine */ int daxpy_();
    static integer jj;


/*     internal variables */


/*     begin block permitting ...exits to 150 */

/*        check for zero diagonal elements. */

    /* Parameter adjustments */
    --b;
    t_dim1 = *ldt;
    t_offset = t_dim1 + 1;
    t -= t_offset;

    /* Function Body */
    i__1 = *n;
    for (*info = 1; *info <= i__1; ++(*info)) {
    if (t[*info + *info * t_dim1] == 0.) {
        goto L150;
    }
/*     ......exit */
/* L10: */
    }
    *info = 0;

/*     determine the task and go to it. */

    case_ = 1;
    if (*job % 10 != 0) {
    case_ = 2;
    }
    if (*job % 100 / 10 != 0) {
    case_ += 2;
    }
    switch ((int)case_) {
    case 1:  goto L20;
    case 2:  goto L50;
    case 3:  goto L80;
    case 4:  goto L110;
    }

/* Case 1 (job = 00): */
/*        solve t*x=b for t lower triangular */

L20:
    b[1] /= t[t_dim1 + 1];
    if (*n >= 2) {
    i__1 = *n;
    for (j = 2; j <= i__1; ++j) {
        temp = -b[j - 1];
        i__2 = *n - j + 1;
        daxpy_(&i__2, &temp, &t[j + (j - 1) * t_dim1], &c__1, &b[j], &
            c__1);
        b[j] /= t[j + j * t_dim1];
/* L30: */
    }
    }
    goto L140;

/* Case 2 (job = 01): */
/*        solve t*x=b for t upper triangular. */

L50:
    b[*n] /= t[*n + *n * t_dim1];
    if (*n >= 2) {
    i__1 = *n;
    for (jj = 2; jj <= i__1; ++jj) {
        j = *n - jj + 1;
        temp = -b[j + 1];
        daxpy_(&j, &temp, &t[(j + 1) * t_dim1 + 1], &c__1, &b[1], &c__1);
        b[j] /= t[j + j * t_dim1];
/* L60: */
    }
    }
    goto L140;

/* Case 3 (job = 10): */
/*        solve trans(t)*x=b for t lower triangular. */

L80:
    b[*n] /= t[*n + *n * t_dim1];
    if (*n >= 2) {
    i__1 = *n;
    for (jj = 2; jj <= i__1; ++jj) {
        j = *n - jj + 1;
        i__2 = jj - 1;
        b[j] -= ddot_(&i__2, &t[j + 1 + j * t_dim1], &c__1, &b[j + 1], &
            c__1);
        b[j] /= t[j + j * t_dim1];
/* L90: */
    }
    }
    goto L140;

/* Case 4 (job = 11): */
/*        solve trans(t)*x=b for t upper triangular. */

L110:
    b[1] /= t[t_dim1 + 1];
    if (*n >= 2) {
    i__1 = *n;
    for (j = 2; j <= i__1; ++j) {
        i__2 = j - 1;
        b[j] -= ddot_(&i__2, &t[j * t_dim1 + 1], &c__1, &b[1], &c__1);
        b[j] /= t[j + j * t_dim1];
/* L120: */
    }
    }

L140:
/*     EXIT: */
L150:
    return 0;
} /* dtrsl_ */
