#pragma once

#include "quantum.h"

#define ___ KC_NO

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments as on the physical keyboard
// The second converts the arguments into the 2-D scanned array

#define LAYOUT(                                   \
    kC0, kD0, kE0, kC1, kD1, kE1, kC2, kD2, kE2,  \
    k00, k10, k20, k30, k40, k50,                 \
    k01, k11, k21, k31, k41, k51,                 \
    k02, k12, k22, k32, k42, k52,                 \
    k03, k13, k23, k33, k43, k53,                 \
         k14, k24, k34, k54,                      \
                             k56, k55,            \
                                  k35,            \
                        k36, k46, k25,            \
                                                  \
    kC3, kD3, kE3, kC4, kD4, kE4, kC5, kE5, kD5,  \
                   k60, k70, k80, k90, kA0, kB0,  \
                   k61, k71, k81, k91, kA1, kB1,  \
                   k62, k72, k82, k92, kA2, kB2,  \
                   k63, k73, k83, k93, kA3, kB3,  \
                        k64, k84, k94, kA4,       \
              k96, k85,                           \
              k86,                                \
              k66, k75, k65                       \
) {                                              \
    { k00,  k01,  k02,  k03,  ___,  ___,  ___ }, \
    { k10,  k11,  k12,  k13,  k14,  ___,  ___ }, \
    { k20,  k21,  k22,  k23,  k24,  k25,  ___ }, \
    { k30,  k31,  k32,  k33,  k34,  k35,  k36 }, \
    { k40,  k41,  k42,  k43,  ___,  ___,  k46 }, \
    { k50,  k51,  k52,  k53,  k54,  k55,  k56 }, \
    { k60,  k61,  k62,  k63,  k64,  k65,  k66 }, \
    { k70,  k71,  k72,  k73,  ___,  k75,  ___ }, \
    { k80,  k81,  k82,  k83,  k84,  k85,  k86 }, \
    { k90,  k91,  k92,  k93,  k94,  ___,  k96 }, \
    { kA0,  kA1,  kA2,  kA3,  kA4,  ___,  ___ }, \
    { kB0,  kB1,  kB2,  kB3,  ___,  ___,  ___ }, \
    { kC0,  kC1,  kC2,  kC3,  kC4,  kC5,  ___ }, \
    { kD0,  kD1,  kD2,  kD3,  kD4,  kD5,  ___ }, \
    { kE0,  kE1,  kE2,  kE3,  kE4,  kE5,  ___ } \
}

/*  ---------------- LEFT HAND -----------------   ---------------- RIGHT HAND ---------------- */
#define LAYOUT_pretty(                                                                           \
    kC0, kD0, kE0, kC1, kD1, kE1, kC2, kD2, kE2,   kC3, kD3, kE3, kC4, kD4, kE4, kC5, kE5, kD5,  \
    k00, k10, k20, k30, k40, k50,                            k60, k70, k80, k90, kA0, kB0,       \
    k01, k11, k21, k31, k41, k51,                            k61, k71, k81, k91, kA1, kB1,       \
    k02, k12, k22, k32, k42, k52,                            k62, k72, k82, k92, kA2, kB2,       \
    k03, k13, k23, k33, k43, k53,                            k63, k73, k83, k93, kA3, kB3,       \
         k14, k24, k34, k54,                                      k64, k84, k94, kA4,            \
                             k56, k55,                  k96, k85,                                \
                                  k35,                  k86,                                     \
                        k36, k46, k25,                  k66, k75, k65                            \
) {                                              \
    { k00,  k01,  k02,  k03,  ___,  ___,  ___ }, \
    { k10,  k11,  k12,  k13,  k14,  ___,  ___ }, \
    { k20,  k21,  k22,  k23,  k24,  k25,  ___ }, \
    { k30,  k31,  k32,  k33,  k34,  k35,  k36 }, \
    { k40,  k41,  k42,  k43,  ___,  ___,  k46 }, \
    { k50,  k51,  k52,  k53,  k54,  k55,  k56 }, \
    { k60,  k61,  k62,  k63,  k64,  k65,  k66 }, \
    { k70,  k71,  k72,  k73,  ___,  k75,  ___ }, \
    { k80,  k81,  k82,  k83,  k84,  k85,  k86 }, \
    { k90,  k91,  k92,  k93,  k94,  ___,  k96 }, \
    { kA0,  kA1,  kA2,  kA3,  kA4,  ___,  ___ }, \
    { kB0,  kB1,  kB2,  kB3,  ___,  ___,  ___ }, \
    { kC0,  kC1,  kC2,  kC3,  kC4,  kC5,  ___ }, \
    { kD0,  kD1,  kD2,  kD3,  kD4,  kD5,  ___ }, \
    { kE0,  kE1,  kE2,  kE3,  kE4,  kE5,  ___ }  \
}

/*
Unused matrix positions
k06…: 11 positions, J9 connector
k04…: other (11)
*/
#define LAYOUT_all(                            \
    kC0, kD0, kE0, kC1, kD1, kE1, kC2, kD2, kE2,   kC3, kD3, kE3, kC4, kD4, kE4, kC5, kE5, kD5,  \
    k00, k10, k20, k30, k40, k50,                            k60, k70, k80, k90, kA0, kB0,       \
    k01, k11, k21, k31, k41, k51,                            k61, k71, k81, k91, kA1, kB1,       \
    k02, k12, k22, k32, k42, k52,                            k62, k72, k82, k92, kA2, kB2,       \
    k03, k13, k23, k33, k43, k53,                            k63, k73, k83, k93, kA3, kB3,       \
         k14, k24, k34, k54,                                      k64, k84, k94, kA4,            \
                             k56, k55,                  k96, k85,                                \
                                  k35,                  k86,                                     \
                        k36, k46, k25,                  k66, k75, k65,                           \
    k06, k16, k26, kA6, kB6, kC6, kD6, kE6,                                                      \
    k04, k44, k74, kB4, k05, k15, k45, k95, kA5, kB5, k76                                        \
) {                                              \
    { k00,  k01,  k02,  k03,  k04,  k05,  k06 }, \
    { k10,  k11,  k12,  k13,  k14,  k15,  k16 }, \
    { k20,  k21,  k22,  k23,  k24,  k25,  k26 }, \
    { k30,  k31,  k32,  k33,  k34,  k35,  k36 }, \
    { k40,  k41,  k42,  k43,  k44,  k45,  k46 }, \
    { k50,  k51,  k52,  k53,  k54,  k55,  k56 }, \
    { k60,  k61,  k62,  k63,  k64,  k65,  k66 }, \
    { k70,  k71,  k72,  k73,  k74,  k75,  k76 }, \
    { k80,  k81,  k82,  k83,  k84,  k85,  k86 }, \
    { k90,  k91,  k92,  k93,  k94,  k95,  k96 }, \
    { kA0,  kA1,  kA2,  kA3,  kA4,  kA5,  kA6 }, \
    { kB0,  kB1,  kB2,  kB3,  KB4,  KB5,  KB6 }, \
    { kC0,  kC1,  kC2,  kC3,  kC4,  kC5,  KC6 }, \
    { kD0,  kD1,  kD2,  kD3,  kD4,  kD5,  KD6 }, \
    { kE0,  kE1,  kE2,  kE3,  kE4,  kE5,  KE6 }  \
}
