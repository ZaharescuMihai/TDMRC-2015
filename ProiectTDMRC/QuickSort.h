#ifndef QUICKSORTH
#define QUICKSORTH
#include <stack>
#include <algorithm>
#include <deque>

template <class T, typename C = std::less<typename T> >
class QuickSort
{

private:
	static int choosePivot(T *A, int lo, int hi)
	{
		return (lo+hi)/2;
	}

	inline static void swap(T &a, T &b)
	{
		T x = a;
		a=b;
		b=x;
	}

	// lo is the index of the leftmost element of the subarray
	// hi is the index of the rightmost element of the subarray (inclusive)

	static int  partition(T *A, int lo, int hi)
	{
		int pivotIndex = choosePivot(A, lo, hi);
		T pivotValue = A[pivotIndex];

		// put the chosen pivot at A[hi]
		swap(A[pivotIndex], A[hi]);
		int storeIndex = lo;

		C comparator;

		// Compare remaining array elements against pivotValue = A[hi]
		for (int i=lo; i<=hi; i++)
		{
			if (comparator(A[i], pivotValue)) //<
			{
				swap(A[i], A[storeIndex]);
				storeIndex = storeIndex + 1;
			}
		}

		swap(A[storeIndex], A[hi]);  // Move pivot to its final place
		return storeIndex;
	}








	static void quicksort(T *A, int lo, int hi)
	{
		if (lo < hi)
		{
			int p = partition(A, lo, hi);
			quicksort(A, lo, p - 1);
			quicksort(A, p + 1, hi);
		}
	}

	struct RecState
	{
		int lo, hi, p;
		char operation;

		RecState()
		{
		}

		RecState(int lo, int hi, int p, char operation)
		{
			this->lo = lo;
			this->hi = hi;
			this->p = p;
			this->operation = operation;
		}
	};

	static void nonrecursive_quicksort(T *A, int lo, int hi)
	{
		std::deque<struct RecState> mydeque (hi-lo); 
		std::stack<struct RecState> recursive(mydeque);

		struct RecState initial;	
		initial.lo = lo;	
		initial.hi = hi;	
		initial.operation = 0;
		recursive.push(initial);

		struct RecState *rec_params;

		while(!recursive.empty())
		{
			rec_params = &recursive.top();

			if(rec_params->lo < rec_params->hi)
			{
				if(rec_params->operation == 0)
				{
					rec_params->p = partition(A, rec_params->lo, rec_params->hi);
					recursive.push(struct RecState(rec_params->lo, rec_params->p - 1, 0, 0));
					rec_params->operation = 1;
				}
				else if(rec_params->operation == 1)
				{
					recursive.push(struct RecState(rec_params->p + 1, rec_params->hi, 0, 0));
					rec_params->operation = 2;
				}
				else
				{
					recursive.pop();
				}
			}
			else
			{
				recursive.pop();
			}
		}
	}

public:
	static void quicksort(T *data, int nr_elements)
	{
		//nonrecursive_quicksort(data, 0, nr_elements-1);
		//quicksort(data, 0, nr_elements-1);

		std::vector<T> myvector (data, data + nr_elements); 
		C comp;
		std::sort (myvector.begin(), myvector.end(), comp);
		memcpy( data, &myvector[ 0 ], sizeof( T ) * nr_elements );
	}
};

#endif