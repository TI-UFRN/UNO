all: main.c _creation_helper _print_helper _card_helper _hand_helper _logic_helper
	gcc main.c creationHelper.o printHelper.o cardHelper.o handHelper.o logicHelper.o -o Pablo.bot
_creation_helper: helpers/creationHelper.c 
	gcc helpers/creationHelper.c -c
_print_helper: helpers/printHelper.c 
	gcc helpers/printHelper.c -c
_card_helper: helpers/cardHelper.c
	gcc helpers/cardHelper.c -c
_hand_helper: helpers/handHelper.c
	gcc helpers/handHelper.c -c
_logic_helper: helpers/logicHelper.c
	gcc helpers/logicHelper.c -c