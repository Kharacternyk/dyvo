DEPS = pangocairo md4c librsvg-2.0 libconfig

debug: format check build generate show

show:
	@impressive -qt None slides.d/dyvo2.pdf

generate:
	@cd slides.d && ../dyvo

build:
	@gcc `pkg-config --cflags $(DEPS)` -o dyvo -g -Werror -Wall *.c \
		`pkg-config --libs $(DEPS)`

check:
	@cppcheck --suppress=missingIncludeSystem --template=gcc \
	          --quiet --platform=unix64 --enable=all *.c

format:
	@astyle --formatted --project *.c *.h

graph:
	@cinclude2dot | xdot -

valgrind:
	@cd slides.d && valgrind ../dyvo
