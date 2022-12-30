#define _CRT_SECURE_NO_WARNINGS

#include "BankAccount.h"
#include <stdio.h>
#include <stdlib.h>


BankAccount* create_account() {
	double initial_balance = 0;
	printf("Initial balance, dude ");
	fflush(stdout);
	scanf(" %lf", &initial_balance);
	return BankAccount_construct(initial_balance);
}


char prompt(void) {
	char c;
	printf("The actions, dude:\n"
		"d: deposit money, dude\n"
		"w: withdraw money, dude\n"
		"g: get balence, dude\n"
		"s: show transations, dude\n"
		"q: quit, dude\n");
	printf("========================================");
	printf("\nWhatcha want, dude ");
	fflush(stdout);
	scanf(" %c", &c);
	return c;
}

double get_amount() {
	double amount = 0;
	printf("how much money, dude ");
	fflush(stdout);
	scanf(" %lf", &amount);
	return amount;
}

void print_balance(BankAccount* ba) {
	printf("balance, dude %lf\n", BankAccount_get_balance(ba));
	fflush(stdout);
}

void handle_deposit(BankAccount* ba) {
	BankAccount_deposit(ba, get_amount());
	print_balance(ba);
	printf("deposited money, dude\n");
	fflush(stdout);
}

void handle_withdrawal(BankAccount* ba) {
	BankAccount_withdraw(ba, get_amount());
	print_balance(ba);
	printf("withdrew money, dude\n");
	fflush(stdout);
}

void handle_get_balance(BankAccount* ba) {
	print_balance(ba);
	fflush(stdout);
}

void handle_show_transactions(BankAccount* ba) {
	printf("last deposit, dude %lf\n", BankAccount_get_last_deposit(ba));
	printf("last withdrawl, dude %lf\n", BankAccount_get_last_withdrawal(ba));
	print_balance(ba);
	fflush(stdout);
	printf("showed transactions, dude\n");
	fflush(stdout);
}

/*
 * A bank account program utilizing BankAccount.
 */
int main(int argc, char* argv[]) {

	/* Get the initial balance of the two accounts. */
	double initial_balance = 0;
	BankAccount* ba = create_account();

	/* Start the main loop. */
	int done = 0;
	while (!done) {
		/* Prompt and get input. */
		char input = prompt();
		/* Handle the correct operation based on the input. */
		if (input == 'd') {
			handle_deposit(ba);
		}
		else if (input == 'w') {
			handle_withdrawal(ba);
		}
		else if (input == 'g') {
			handle_get_balance(ba);
		}
		else if (input == 's') {
			handle_show_transactions(ba);
		}
		/* If quit, set the done flag. */
		else if (input == 'q') {
			done = 1;
		}
	}
	printf("ok bye, dude\n");
	fflush(stdout);
	return 0;
}
