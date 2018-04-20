#Jocelyn Malanco
#jcm160330@utdallas.edu
#CS 3377

CXX = g++
CXXFLAGS = -Wall -g
CPPFLAGS =  -I/scratch/perkins/include

LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses

PROJECTNAME = Program6.backup

EXECFILE = cdkexample

OBJS = cdkexample.o

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*

$(EXECFILE):	$(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "'pwd'"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME) -$(shell date + 'Y.%m.%d-%H:%M:%s').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

