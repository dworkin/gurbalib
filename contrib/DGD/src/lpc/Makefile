#
# This file is part of DGD, http://dgd-osr.sourceforge.net/
# Copyright (C) 1993-2010 Dworkin B.V.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
HOST=	DARWIN
DEFINES=-D$(HOST)
DEBUG=	-O -g
CCFLAGS=$(DEFINES) $(DEBUG)
CFLAGS=	-I. -I.. -I../comp $(CCFLAGS)
LIBS=
LINTFLAGS=-abcehpruz
CC=	gcc
DMAKE=	make
YACC=	yacc
PRECOMP=../comp/a.out
CONFIG=	../../../../gurba.dgd
MUDLIB=	../../../../lib

#SRC=    driver.c auto.c auto-game.c auto-kernel.c compiler_d.c secure_d.c
SRC=

#OBJ=	driver.o auto.o auto-game.o auto-kernel.o compiler_d.o secure_d.o
OBJ=

dgd:	$(OBJ) lpc.o
	@for i in $(OBJ) lpc.o; do echo lpc/$$i; done > dgd

lint:
	lint $(LINTFLAGS) $(CFLAGS) lpc.c

$(SRC):	$(PRECOMP)

$(PRECOMP):
	cd ../comp; $(DMAKE) 'DMAKE=$(DMAKE)' 'CC=$(CC)' 'CCFLAGS=$(CCFLAGS)' \
			     'YACC=$(YACC)' 'LIBS=$(LIBS)' a.out

driver.c: $(MUDLIB)/kernel/sys/driver.c
	$(PRECOMP) $(CONFIG) /kernel/sys/driver.c $@

auto.c:	$(MUDLIB)/kernel/lib/auto.c
	$(PRECOMP) $(CONFIG) /kernel/lib/auto.c $@

auto-game.c: $(MUDLIB)/kernel/lib/auto-game.c auto.c
	$(PRECOMP) $(CONFIG) /kernel/lib/auto-game.c $@

auto-kernel.c: $(MUDLIB)/kernel/lib/auto-kernel.c auto.c
	$(PRECOMP) $(CONFIG) /kernel/lib/auto-kernel.c $@

compiler_d.c: $(MUDLIB)/kernel/daemons/compiler_d.c auto.c auto-kernel.c
	$(PRECOMP) $(CONFIG) /kernel/daemons/compiler_d.c $@

secure_d.c: $(MUDLIB)/kernel/daemons/secure_d.c auto.c auto-kernel.c
	$(PRECOMP) $(CONFIG) /kernel/daemons/secure_d.c $@

clean:
	rm -f dgd $(SRC) $(OBJ) lpc.o


$(OBJ) lpc.o: ../dgd.h ../config.h ../host.h ../error.h ../alloc.h ../str.h
$(OBJ) lpc.o: ../array.h ../object.h ../xfloat.h ../interpret.h ../data.h

$(OBJ) lpc.o: ../comp/csupport.h

lpc.o:	lpc.c list $(OBJ)
