#ifndef PROCESSOR_EMULATOR_PROGRAMS_H
#define PROCESSOR_EMULATOR_PROGRAMS_H

/* https://www.c64-wiki.com/wiki/Reset_(Process)
; MOS 6510 System Reset routine[3]
; Reset vector (Kernal address $FFFC) points here.
;
; If cartridge is detected then cartridge cold start routine is activated.
; If no cartridge is detected then I/O and memory are initialised and BASIC cold start routine is activated.

FCE2   A2 FF      LDX #$FF        ;
FCE4   78         SEI             ; set interrupt disable
FCE5   9A         TXS             ; transfer .X to stack
FCE6   D8         CLD             ; clear decimal flag
FCE7   20 02 FD   JSR $FD02       ; check for cart
FCEA   D0 03      BNE $FCEF       ; .Z=0? then no cart detected
FCEC   6C 00 80   JMP ($8000)     ; direct to cartridge cold start via vector
FCEF   8E 16 D0   STX $D016       ; sets bit 5 (MCM) off, bit 3 (38 cols) off
FCF2   20 A3 FD   JSR $FDA3       ; initialise I/O
FCF5   20 50 FD   JSR $FD50       ; initialise memory
FCF8   20 15 FD   JSR $FD15       ; set I/O vectors ($0314..$0333) to kernal defaults
FCFB   20 5B FF   JSR $FF5B       ; more initialising... mostly set system IRQ to correct value and start
FCFE   58         CLI             ; clear interrupt flag
FCFF   6C 00 A0   JMP ($A000)     ; direct to BASIC cold start via vector
*/

std::string RESET_ROUTINE = "A2 FF 78 9A D8 20 02 FD D0 03 "
                            "6C 00 80 8E 16 D0 20 A3 FD 20 50 FD "
                            "20 15 FD 20 5B FF 58 6C 00 A0";

#endif
