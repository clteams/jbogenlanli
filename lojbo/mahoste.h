#ifndef __MAHOSTE__
#define __MAHOSTE__ 1

#define CMAVOCNT 599 

enum cmavo {
A,
E,
O,
U,
JI,

BAhI,
BAI,
BAU,
BEhI,
CAhI,
CAU,
CIhE,
CIhO,
CIhU,
CUhU,
DEhI,
DIhO,
DOhE,
DUhI,
DUhO,
FAhE,
FAU,
FIhE,
GAhA,
GAU,
JAhE,
JAhI,
JIhE,
JIhO,
JIhU,
KAhA,
KAhI,
KAI,
KIhI,
KIhU,
KOI,
KUhU,
LAhU,
LEhA,
LIhE,
MAhE,
MAhI,
MAU,
MEhA,
MEhE,
MUhI,
MUhU,
NIhI,
PAhA,
PAhU,
PIhO,
POhI,
PUhA,
PUhE,
RAhA,
RAhI,
RAI,
RIhA,
RIhI,
SAU,
SIhU,
TAhI,
TAI,
TIhI,
TIhU,
TUhI,
VAhO,
VAhU,
ZAU,
ZUhE,

BAhE,
ZAhE,

BE,

BEI,

BEhO,

BIhI,
BIhO,
MIhI,

BO,

BU,

GAhE,
TOhA,
LOhA,
GEhO,
JEhO,
JOhO,
RUhO,
SEhE,
NAhA,
BY,
CY,
DY,
FY,
GY,
JY,
KY,
LY,
MY,
NY,
PY,
RY,
SY,
TY,
VY,
XY,
ZY,
YBU,
YhY,
CAhA,
KAhE,
NUhO,
PUhI,

CAI,
CUhI,
PEI,
RUhE,
SAI,

CEI,

CEhE,

CO,

COI,
COhO,
VIhO,
TAhA,
REhI,
PEhU,
NUhE,
MUhO,
MIhE,
KIhE,
KEhO,
JUhI,
JEhE,
FIhI,
FEhO,
BEhE,

CU,

CUhE,
NAU,

DAhO,

DOI,

DOhU,

FA,
FE,
FI,
FO,
FU,
FAI,
FIhA,

BEhA,
BUhU,
CAhU,
DUhA,
FAhA,
GAhU,
NEhA,
NEhI,
NEhU,
NIhA,
PAhO,
REhO,
RIhU,
RUhU,
TEhE,
TIhA,
TOhO,
VUhA,
ZEhO,
ZOhA,
ZOhI,
ZUhA,

FAhO,

FEhE,

FEhU,

FIhO,

FOI,

FUhE,

FUhO,

GA,
GE,
GO,
GU,
GEhI,

GEhU,

GI,

GIhA,
GIhE,
GIhO,
GIhU,
GIhI,

GOI,
PE,
NE,
PO,
POhE,
POhU,
NOhU,

BUhA,
BUhE,
BUhI,
GOhA,
GOhE,
GOhI,
GOhO,
GOhU,
COhE,
DU,
MO,
NEI,
NOhA,

GUhA,
GUhE,
GUhO,
GUhU,
GUhI,

I,

JA,
JE,
JO,
JU,
JEhI,

JAI,

CE,
CEhO,
FAhU,
PIhU,
JOhE,
JOhU,
JOI,
JUhE,
KUhA,

KEhE,

KE,

KEI,

KI,

KOhA,
KOhE,
KOhI,
KOhO,
KOhU,
FOhA,
FOhE,
FOhI,
FOhO,
FOhU,
VOhA,
VOhE,
VOhI,
VOhO,
VOhU,
TI,
TA,
TU,
RI,
RA,
RU,
MI,
DO,
KO,
MA,
MIhO,
MIhA,
MAhA,
DOhO,
ZUhI,
ZIhO,
ZOhE,
DA,
DE,
DI,
DOhI,
CEhU,
KEhA,
DIhE,
DEhE,
DAhE,
DIhU,
DEhU,
DAhU,

KU,

KUhO,

LA,
LAhI,
LAI,

CEhA,
LAU,
TAU,
ZAI,

LAhE,
LUhA,
LUhE,
LUhI,
LUhO,
TUhA,
VUhI,

LE,
LO,
LEI,
LOI,
LEhI,
LOhI,
LEhE,
LOhE,

LEhU,

LI,
MEhO,

LIhU,

LOhO,

LOhU,

LU,

LUhU,

ME,

MEhU,

MOhI,

JAhA,
NA,

NAI,

JEhA,
NAhE,
NOhE,
TOhE,

NIhO,
NOhI,

NOI,
POI,
VOI,

NU,
NI,
KA,
JEI,
SIhO,
DUhU,
LIhI,
SUhU,
MUhE,
PUhU,
ZAhI,
ZUhO,

NUhI,

NUhU,

PEhE,

PU,
CA,
BA,

RAhO,

REhU,
ROI,

SA,

SE,
TE,
VE,
XE,

SEI,
TIhO,

SEhU,

SI,

SOI,

SU,

DIhI,
NAhO,
RUhI,
TAhE,

TEI,

TO,
TOhI,

TOI,

TUhE,

TUhU,

AhA,
AhE,
AhI,
AhO,
AhU,
AI,
AU,
BAhA,
BAhU,
BEhU,
BIhU,
BUhO,
CAhE,
DAhI,
DAI,
DOhA,
EhA,
EhE,
EhI,
EhO,
EhU,
EI,
FUhI,
GAhI,
GEhE,
IhA,
IhE,
IhI,
IhO,
IhU,
IA,
IE,
II,
IO,
IU,
JAhO,
JEhU,
JIhA,
JOhA,
JUhA,
JUhO,
KAhU,
KAU,
KEhU,
KIhA,
KUhI,
LAhA,
LEhO,
LIhA,
LIhO,
MIhU,
MUhA,
NAhI,
OI,
OhA,
OhE,
OhI,
OhO,
OhU,
PAhE,
PAU,
PEhA,
PEhI,
POhO,
RAhU,
REhE,
RIhE,
ROhA,
ROhE,
ROhI,
ROhO,
ROhU,
RUhA,
SAhA,
SAhE,
SAhU,
SEhA,
SEhI,
SEhO,
SIhA,
SUhA,
TAhO,
TAhU,
TIhE,
TOhU,
UhA,
UhE,
UhI,
UhO,
UhU,
UA,
UE,
UI,
UO,
UU,
VAhI,
VUhE,
XU,
ZAhA,
ZOhO,
ZUhU,
ZIhA,

VI,
VA,
VU,

VAU,

VEhI,
VEhA,
VEhU,
VEhE,

VIhI,
VIhA,
VIhU,
VIhE,

VUhO,

XI,

Y,

PUhO,
CAhO,
BAhO,
COhA,
COhI,
COhU,
DEhA,
DIhA,
MOhU,
ZAhO,

ZEhI,
ZEhA,
ZEhU,
ZEhE,

ZEI,

ZI,
ZA,
ZU,

ZIhE,

ZO,

LAhO,
ZOI,

ZOhU,

BIhE,

BOI,

FUhA,

GAhO,
KEhI,

JOhI,

KUhE,

MAI,
MOhO,

MAhO,

SIhE,
VAhE,
MEI,
MOI,
CUhO,

MOhE,

NAhU,

NIhE,

NUhA,

PA,
RE,
CI,
VO,
MU,
XA,
ZE,
BI,
SO,
NO,
DAU,
FEI,
GAI,
JAU,
REI,
VAI,
RO,
XO,
CEhI,
CIhI,
DAhA,
DUhE,
FIhU,
JIhI,
KAhO,
KIhO,
MAhU,
MEhI,
MOhA,
NIhU,
NOhO,
PAI,
PI,
PIhE,
RAhE,
RAU,
SOhA,
SOhE,
SOhI,
SOhO,
SOhU,
SUhE,
SUhO,
TEhO,
TUhO,
ZAhU,

PEhO,

TEhU,

VEI,

VEhO,

CUhA,
DEhO,
FAhI,
FEhA,
FEhI,
FUhU,
GEhA,
GEI,
JUhU,
NEhO,
PAhI,
PIhA,
PIhI,
REhA,
RIhO,
SAhI,
SAhO,
SIhI,
SUhI,
TEhA,
VAhA,
VUhU,

CMENE,
BRIVLA
};

extern cmavo dettype(/*enum yytokentype sm,*/const char *const);

#endif
