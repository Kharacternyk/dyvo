debug: format check build generate show

show:
	@impressive -qt None slides.d/dyvo.pdf

generate:
	@cd slides.d && ../dyvo

build:
	@gcc `pkg-config --cflags pangocairo md4c` -o dyvo -Wall *.c \
		`pkg-config --libs md4c pangocairo`

check:
	@cppcheck --suppress=missingIncludeSystem --template=gcc \
	          --quiet --platform=unix64 --enable=all *.c

format:
	@astyle --formatted --project *.c *.h

graph:
	@cinclude2dot | xdot -

