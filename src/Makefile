debug: format check build
	@cd slides.d && ../dyvo && impressive -qt SlideUp dyvo.pdf

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

