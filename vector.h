#ifndef VECTOR_H_
#define VECTOR_H_
/** forward declaration to an internal hidden vector structure. */
typedef struct vector_struct *vector;

/** create a (zero filled) N dimensional int vector.
 *  @param n the length of the vector 0<n
 *  @return a N-dimensional int vector reference
 */
vector createVector(unsigned short n);
/**
 * remove a vector freeing allocated memory.
 *  @param a valid vector reference
 */
void rmVector(vector v);

/** @return length N of the vector */
unsigned short size(vector v);
/** access to the internal data array.*/
int* values(vector v);
/** get the vector entry with index j
 * @param v vector reference
 * @param j the index number  0<=j < N
 * @return the entry
 * @print error and exits if dimensions wrong
 */
int getValue(vector v, unsigned short j);
/** set the vector entry with index j
 * @param v vector reference
 * @param j the index number  0<=j < N
 * @param value the entry to set
 * @print error and exits if dimensions wrong
 */
void setValue(vector v, unsigned short j, int value);
/** scalar product between to vectors.
 * @param a vector reference
 * @param a vector reference
 * @return scalar product a*b
 * @print error and exits if dimensions wrong
 */
int vectorDotVector(vector a, vector b);
/** addition of two vectors.
 * @param a vector reference
 * @param a vector reference
 * @return c=a+b vector
 * @print error and exits if dimensions wrong
 */
vector vectorPlusVector(vector a, vector b);
#endif /* VECTOR_H_ */