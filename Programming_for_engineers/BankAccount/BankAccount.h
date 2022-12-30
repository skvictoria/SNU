#pragma once

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <stdlib.h>
#include <float.h> /* Used for DBL_MAX, DBL_MIN */

/*
 * Models data for a BankAccount. An opaque type that
 * can only be used through an opaque pointer.
 *
 * - Stores the most recent last withdrawal and last deposit amounts as well.
 */
typedef struct BankAccount BankAccount;

/*
 * Allocates a new BankAccount with a set balance.
 */
BankAccount* BankAccount_construct(double balance);

/*
 * Destroys a BankAccount by freeing its memory.
 */
void BankAccount_destroy(BankAccount* ba);

/*
 * Performs a deposit on an account.
 *
 * - Bonus feature: checking for overflow/underflow.
 *   - Does not modify ba->balance on error.
 *
 * Returns: 0 on success, 1 on overflow, -1 on underflow.
 */
int BankAccount_deposit(BankAccount* ba, double amount);

/*
 * Performs a withdrawal on a BankAccount.
 *
 */
int BankAccount_withdraw(BankAccount* ba, double amount);

/*
 * Gets the balance for a BankAccount.
 */
double BankAccount_get_balance(BankAccount* ba);

/*
 * Gets the last deposit amount for a BankAccount.
 */

double BankAccount_get_last_deposit(BankAccount* ba);

/*
 * Gets the last withdrawl amount for a BankAccount.
 */
double BankAccount_get_last_withdrawal(BankAccount* ba);


#endif /* BANKACCOUNT_H */

