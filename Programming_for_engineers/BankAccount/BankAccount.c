#include "BankAccount.h"

struct BankAccount {
	double balance;
	double last_withdrawl;
	double last_deposit;
};

/*
 * Allocates a new BankAccount with a set balance.
 */
BankAccount* BankAccount_construct(double balance) {
	struct BankAccount* account = (struct BankAccount*)malloc(sizeof(struct BankAccount));
	account->balance = balance;
	return account;
}

/*
 * Destroys a BankAccount by freeing its memory.
 */
void BankAccount_destroy(BankAccount* ba) {
	free(ba);
}

/*
 * Performs a deposit on an account.
 *
 * - Bonus feature: checking for overflow/underflow.
 *   - Does not modify ba->balance on error.
 *
 * Returns: 0 on success, 1 on overflow, -1 on underflow.
 */

int BankAccount_deposit(BankAccount* ba, double amount) {

	if (ba->balance <= DBL_MAX - amount) {
		ba->balance += amount;
		ba->last_deposit = amount;
		return 0;
	}
	else {
		return 1;
	}
}
/*
 * Performs a withdrawal on a BankAccount.
 *
 */
int BankAccount_withdraw(BankAccount* ba, double amount) {
	if (ba->balance >= amount + DBL_MIN) {
		ba->balance -= amount;
		ba->last_deposit = amount;

		return 0;
	}
	else {
		return -1;
	}
}
/*
 * Gets the balance for a BankAccount.
 */
double BankAccount_get_balance(BankAccount* ba) {
	return ba->balance;
}
/*
 * Gets the last deposit amount for a BankAccount.
 */

double BankAccount_get_last_deposit(BankAccount* ba) {
	return ba->last_deposit;
}

/*
 * Gets the last withdrawl amount for a BankAccount.
 */
double BankAccount_get_last_withdrawal(BankAccount* ba) {
	return ba->last_withdrawl;
}

