CC = gcc
FILES = xbmc-es-switch.c
PROGRAMS = xbmc-es-switch
SERVICES = xbmc-es-switch.service
SDDIR = lib/systemd/system
UDEVRULES = 99-joystick.rules
UDEVDIR = etc/udev/rules.d

prefix = /usr

$(PROGRAMS): $(FILES)
	$(CC) $(FILES) -o $(PROGRAMS)


.PHONY: install
install: $(PROGRAMS)
	test -d $(DESTDIR)/$(prefix)/bin || mkdir --parents $(DESTDIR)/$(prefix)/bin
	for p in $(PROGRAMS); do \
		install -m 0755 $$p $(DESTDIR)/$(prefix)/bin; \
	done
	
	test -d $(DESTDIR)/$(prefix)/$(SDDIR) || mkdir --parents $(DESTDIR)/$(prefix)/$(SDDIR)
	for d in $(SERVICES); do \
		install -m 0644 $$d $(DESTDIR)/$(prefix)/$(SDDIR); \
	done
	
	test -d $(DESTDIR)/$(UDEVDIR) || mkdir --parents $(DESTDIR)/$(UDEVDIR)
	for d in $(UDEVRULES); do \
		install -m 0644 $$d $(DESTDIR)/$(UDEVDIR); \
	done

.PHONY: clean
clean:
	rm -f $(PROGRAMS)

