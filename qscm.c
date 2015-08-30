#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef intptr_t V;

#define L(n) L_(n, E)
#define A a_(E)
#define B(x,y) (E=C(x,E), B_(y, &E))
#define F(n) C((V)f##n, E)
#define Z1(f) Zn(f, 0)
#define Z(f,a) Zn(f, C(a,0))
#define Z3(f,a,b) Zn(f, C(a,C(b,0)))
#define Z4(f,a,b,c) Zn(f, C(a,C(b,C(c,0))))
#define J return
#define D(x,y) V f##x(V E){J y;}

V C(V a,V d){V*p=malloc(2*sizeof*p);*p=a;p[1]=d;J(V)p;}
V a_(V x){J*(V*)x;}
V d_(V x){J*((V*)x+1);}
V B_(V x,V *e){*e=d_(*e);J x;}
V L_(V n,V e){while(--n)e=d_(e);J a_(e);}
V Zn(V x,V a){V(*f)(V)=(V(*)())a_(x),e=d_(x);for(;a;e=a,a=x)x=d_(a),((V*)a)[1]=e;J f(e);}

D(g,*(char *)A)
D(s,*(char *)L(2)=A)
D(n,(V)malloc(A))
D(c,C(L(2),A))
D(a,a_(A))
D(d,d_(A))
D(i,getchar())
D(o,putchar(A))
#define X(x) (V)&(V[2]){(V)f##x}
V qget=X(g),qset=X(s),qnew=X(n),q=X(c),qcar=X(a),qcdr=X(d),qgetc=X(i),qputc=X(o),
qn,qC,qF,qQ,qqqc,qaritop,qbuiltins,qL,qS,qitrs,qputi,qqd4,qqd3,qqd2,qqd,qpos,qreserved,qglo,qinqw,qlen,qfns,qqpqp,qqes,qarg,qapp,qnil,qcompn,qcomp,qnxt,qseqq,qtok,qbget,qpeek;
D(1,B(qpeek,((qpeek=Z1(qgetc)),A)))
D(2,((A==9)+(A==10)+(A==32)))
D(3,(Z3(qset,A,Z1(qbget)),B((1+A),(((qpeek=='"')+(L(3)*(Z(L(4),qpeek)+(qpeek=='(')+(qpeek==')')+(qpeek=='#'))))?Z3(qset,A,0):Z3(qseqq,L(3),A)))))
D(4,B(qpeek,(Z(L(2),A)?(Z1(qbget),Z1(qnxt)):(((A=='(')+(A==')'))?Z1(qbget):((A=='"')?((qtok=Z(qnew,64)),Z3(qseqq,0,qtok),Z1(qbget),'s'):((A=='#')?(Z1(qbget),(qtok=Z1(qbget)),'c'):((qtok=Z(qnew,16)),Z3(qseqq,1,qtok),((('0'<=A)*(A<='9'))?'n':'w'))))))))
D(5,B(Z1(qnxt),(Z4(qcomp,L(2),A,qtok))))
D(6,((L(2)==')')?qnil:B(Z4(qcomp,L(3),L(2),A),B(Z1(qnxt),Z3(q,L(2),Z4(qapp,L(5),A,qtok))))))
D(7,((Z1(qnxt)==')')?qnil:B(qtok,B(Z1(qarg),Z3(q,L(2),A)))))
D(8,((L(2)=='(')?B(Z1(qnxt),B(((A=='w')?qtok:(V)""),(Z3(qqes,A,(V)"fun")?B(((Z1(qnxt)=='(')?Z1(qarg):Z1('F')),B(Z(qcompn,Z3(qqpqp,A,L(6))),((qfns=Z3(q,A,qfns)),Z1(qnxt),Z3(q,'F',(Z(qlen,qfns)-1))))):(Z3(qqes,A,(V)"let")?B((Z1(qnxt),qtok),B(Z(qcompn,L(6)),B(Z(qcompn,Z3(q,L(2),L(7))),(Z1(qnxt),Z3(q,'B',Z3(q,L(2),A)))))):(Z3(qqes,A,(V)"def")?B((Z1(qnxt),qtok),B(Z(qcompn,L(6)),((Z3(qinqw,L(2),qglo)?0:(qglo=Z3(q,L(2),qglo))),Z1(qnxt),Z3(q,'D',Z3(q,L(2),A))))):Z3(q,'a',Z4(qapp,L(5),L(2),qtok))))))):((L(2)=='w')?(Z3(qinqw,A,qreserved)?Z3(q,'w',qtok):(Z3(qinqw,A,L(3))?Z3(q,'L',Z3(qpos,A,L(3))):((Z3(qinqw,qtok,qglo)?0:(qglo=Z3(q,qtok,qglo))),Z3(q,'G',qtok)))):(((L(2)=='n')+(L(2)=='c')+(L(2)=='s'))?Z3(q,L(2),A):Z1('c')))))
D(9,Z(L(3),Z(L(2),A)))
D(10,F(9))
D(11,(A?(1+Z(qlen,Z(qcdr,A))):0))
D(12,(L(2)?Z3(qqpqp,Z(qcdr,L(2)),Z3(q,Z(qcar,L(2)),A)):A))
D(13,(A?(Z3(qqes,L(2),Z(qcar,A))?0:B(Z3(qpos,L(2),Z(qcdr,A)),((A>=0)+A))):(0-1)))
D(14,(Z3(qpos,L(2),A)>=0))
D(15,B((A-(10*(A/10))),(L(2)?(Z(qputi,(L(2)/10)),Z(qputc,('0'+A))):0)))
D(16,B(Z(qget,L(2)),B(Z(qget,L(2)),((L(2)==A)?(L(2)?Z3(qqes,(1+L(4)),(1+L(3))):1):0))))
D(17,(Z(qget,A)?(Z(L(2),Z(qget,A)),Z3(qitrs,L(2),(1+A))):0))
D(18,Z3(qitrs,qputc,A))
D(19,(A?(Z(L(3),Z(qcar,A)),(Z(qcdr,A)?Z(qS,L(2)):0),Z4(qL,L(3),L(2),Z(qcdr,A))):0))
D(20,B(Z(qget,A),((A==L(3))?(Z(qputc,'q'),Z(qputc,Z(qget,(1+L(2))))):(A?Z3(qqqc,L(3),(2+L(2))):Z(qputc,L(3))))))
D(21,Z3(qqqc,A,(V)"qq@a!b-m+p*s.d=e?w's"))
D(22,(Z(qputc,'q'),(Z3(qqes,A,(V)"cons")?0:Z3(qitrs,F(21),A))))
D(23,(Z(L(2),A),Z(qF,L(3))))
D(24,F(23))
D(25,(Z4(qL,qC,L(2),A),Z(qF,L(5))))
D(26,B((1+A),B(F(24),B(Z(qget,L(3)),((A=='*')?F(25):((A=='%')?Z(L(2),qC):((A=='#')?Z(L(2),qputi):(A?Z(Z(L(2),qputc),A):0))))))))
D(27,B(Z(qcar,A),B(Z(qcdr,L(2)),((L(2)=='F')?Z(Z(qF,(V)"F(#)"),(1+A)):((L(2)=='G')?Z(qQ,A):((L(2)=='L')?(A?Z(Z(qF,(V)"L(#)"),(1+A)):Z(qS,(V)"A")):((L(2)=='a')?B(((Z(qcar,Z(qcar,A))=='w')?Z(qcdr,Z(qcar,A)):(V)""),(Z3(qqes,A,(V)"do")?Z3(Z(qF,(V)"(*)"),(V)",",Z(qcdr,L(2))):(Z3(qqes,A,(V)"if")?Z(Z(Z(Z(qF,(V)"(%?%:%)"),Z(qqd2,L(2))),Z(qqd3,L(2))),Z(qqd4,L(2))):(Z3(qinqw,A,qaritop)?B((Z3(qqes,A,(V)"=")?(V)"==":A),Z3(Z(qF,(V)"(*)"),A,Z(qcdr,L(3)))):((Z(qlen,L(2))<5)?B(Z(qlen,L(2)),Z3(Z(Z(qF,(V)"Z#(*)"),((A==2)?0:A)),(V)",",L(3))):(Z3(Z(qF,(V)"Zn(*,0)"),(V)",C(",L(2)),Z4(qL,qcdr,(V)")",L(2)))))))):((L(2)=='D')?(Z(qS,(V)"("),Z(qQ,Z(qcar,A)),Z(Z(qF,(V)"=%)"),Z(qcdr,A))):((L(2)=='B')?Z(Z(Z(qF,(V)"B(%,%)"),Z(qcar,A)),Z(qcdr,A)):((L(2)=='s')?(Z(qS,(V)"(V)"),Z(qS,A),Z(qputc,'"')):((L(2)=='w')?Z(qQ,A):((L(2)=='c')?(Z(qS,(V)"'"),Z(qputc,A),Z(qS,(V)"'")):((L(2)=='n')?Z(qS,A):Z1('C'))))))))))))))
D(28,(Z(Z(Z(qF,(V)"D(#,%)\n"),qn),A),(qn=(qn+1))))

int main(){V E=0;J ((qpeek=' '),(qbget=F(1)),B(F(2),((qtok=0),(qseqq=F(3)),(qnxt=F(4)))),(qcompn=F(5)),(qapp=F(6)),(qarg=F(7)),(qcomp=F(8)),(qnil=0),(qqd=F(10)),(qqd2=Z3(qqd,qcar,qcdr)),B(Z3(qqd,qcdr,qcdr),((qqd3=Z3(qqd,qcar,A)),(qqd4=Z3(qqd,qqd2,A)))),(qlen=F(11)),(qqpqp=F(12)),(qpos=F(13)),(qinqw=F(14)),(qputi=F(15)),(qqes=F(16)),(qitrs=F(17)),(qS=F(18)),(qL=F(19)),(qbuiltins=Z3(q,(V)"get",Z3(q,(V)"set",Z3(q,(V)"new",Z3(q,(V)"cons",Z3(q,(V)"car",Z3(q,(V)"cdr",Z3(q,(V)"getc",Z3(q,(V)"putc",qnil))))))))),(qaritop=Z3(q,(V)"+",Z3(q,(V)"-",Z3(q,(V)"*",Z3(q,(V)"/",Z3(q,(V)"<",Z3(q,(V)">",Z3(q,(V)"<=",Z3(q,(V)">=",Z3(q,(V)"=",qnil)))))))))),(qreserved=Z3(q,(V)"def",Z3(q,(V)"do",Z3(q,(V)"fun",Z3(q,(V)"if",Z3(q,(V)"let",Z3(qqpqp,qaritop,qbuiltins))))))),(qfns=qnil),(qglo=qnil),(qqqc=F(20)),(qQ=F(22)),(qF=F(26)),(qC=F(27)),B(Z(qcompn,qnil),(Z4(qL,qQ,(V)",",qglo),Z(qS,(V)";\n"),(qn=1),Z4(qL,F(28),(V)"",Z3(qqpqp,qfns,qnil)),Z(Z(qF,(V)"\nint main(){V E=0;J %;}\n"),A))));}
