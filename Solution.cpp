#include <iostream>
#include <vector>
#include <utility>

using namespace std;

typedef unsigned int uint;

uint manji(uint x, uint y)
{
	if (x <= y)
		return x;
	else
		return y;
}

uint put(uint i, uint j, uint M, uint* const cvijece, std::vector<std::pair<uint, uint>>& solution)
{
	solution.push_back(make_pair(i, j));

	if (i == 0 && j == 0)
		return 0;
	else if (i > 0 && j > 0)
	{
		if (cvijece[i * M + (j - 1)] <= cvijece[(i - 1) * M + j])
			return put(i, j - 1, M, cvijece, solution);
		else
			return put(i - 1, j, M, cvijece, solution);
	}
	else if (i == 0)
	{
		return put(0, j - 1, M, cvijece, solution);
	}
	else
		return put(i - 1, 0, M, cvijece, solution);
}

uint solve(const uint N, const uint M, uint16_t* const problem, std::vector<std::pair<uint, uint>>& solution)
{
	uint* cvijece = new uint[N * M];
	int i, j;

	cvijece[0] = problem[0];

	for (i = 1; i < N; ++i)
		cvijece[i * M + 0] = cvijece[(i - 1) * M + 0] + problem[i * M + 0];

	for (j = 1; j < M; ++j)
		cvijece[0 * M + j] = cvijece[0 * M + (j - 1)] + problem[0 * M + j];

	for (i = 1; i < N; ++i)
		for (j = 1; j < M; ++j)
			cvijece[i * M + j] = manji(cvijece[i * M + (j - 1)], cvijece[(i - 1) * M + j]) + problem[i * M + j];

	/*for (i = 0; i < N; ++i)
	{
		for (j = 0; j < M; ++j)
			cout << problem[i * M + j] << " ";
		cout << endl;
	}
	
	cout << endl;

	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < M; ++j)
			cout << cvijece[i * M + j] << " ";
		cout << endl;
	}
	cout << endl;
	*/
	uint kolicina = cvijece[(N-1) * M + (M-1)];

	put(N - 1, M - 1, M, cvijece, solution);

	reverse(solution.begin(), solution.end());

	delete[] cvijece;
	return kolicina;
}

int main()
{
	uint16_t problem[] = { 1, 2, 3, 4, 8, 2, 1, 5, 3 };
	for (int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++)
			cout << problem[i * 3 + j] << " ";
		cout << endl;
	}
	cout << "Trazimo najjeftiniji put od prvog do zadnjeg clana matrice." << endl;
	vector<pair<uint, uint>> solution;
	cout << solve(3, 3, problem, solution) << endl;
	for (auto ir = solution.begin(); ir != solution.end(); ++ir)
		cout << "(" << ir->first << "," << ir->second << ")" << " ";
	cout << endl;
	return 0;
}