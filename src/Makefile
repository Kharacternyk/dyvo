debug: format check build generate show

show:
	@impressive -qt None slides.d/dyvo.pdf

generate:
	@cd slides.d && ../dyvo

build:
	@gcc `pkg-config --cflags pangocairo md4c librsvg-2.0` -o dyvo -g -Werror -Wall *.c \
		`pkg-config --libs md4c pangocairo librsvg-2.0`

check:
	@cppcheck --suppress=missingIncludeSystem --template=gcc \
	          --quiet --platform=unix64 --enable=all *.c

format:
	@astyle --formatted --project *.c *.h

graph:
	@cinclude2dot | xdot -

