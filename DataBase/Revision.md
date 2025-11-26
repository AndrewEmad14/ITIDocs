# Normalization
1NF
	•	All values are atomic (no lists, no multiple values in one cell)
	•	Each record is unique (usually enforced by a primary key)
	•	No repeating groups or arrays

2NF :
	•	It is already in 1NF
	•	No partial dependency:
        Every non-key column must depend on the whole primary key (applies only when primary key is composite).

3NF :
	•	It is already in 2NF
	•	No transitive dependency:
		Non-key columns must not depend on other non-key columns