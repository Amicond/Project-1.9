// 9 Collect Third Terms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
using namespace std;

const string delim = "\\";
const string out_res = "results";

struct st
{
	string name;
	//new
	int len;
	string Type;//C,S or J
	char ops[10];
	int nums[10];
	//end new
	double value[10];
	bool operator==(st r)
	{
		if (name.compare(r.name) == 0)
			return true;
		else
			return false;
	};
};


vector<st> res;
vector<st> long_res;
st c_res;

void decompose(st &cur)
{
	if (cur.name[0] == 'C')
	{
		cur.len = 0;
		cur.Type = "C";
	}
	if (cur.name[0] == 'S')
	{
		cur.len = 1;
		cur.ops[0] = cur.name[1];
		istringstream is;
		is.str(cur.name.substr(2));
		is >> cur.nums[0];
		cur.Type = "S";
	}
	if (cur.name[0] == 'J')
	{
		int temp = cur.name.find_first_not_of("Jpmz");
		cur.len = temp - 1;
		for (int i = 0; i < cur.len; i++)
			cur.ops[i] = cur.name[i + 1];
		istringstream is;
		char tc;
		is.str(cur.name.substr(temp));
		for (int i = 0; i < cur.len; i++)
		{
			is >> cur.nums[i];
			is >> tc;
		}
		cur.Type = "J";
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	//init
	for (int i = 0; i < 10; i++)
		c_res.value[i] = 0;
	//end init
	vector<string> points;
	ifstream config("config.txt", ios::in);
	int num_points,min_order,max_order,cur_term_len;
	string tmp;
	int PiPoint;
	getline(config, tmp);
	config >> num_points;
	getline(config, tmp);
	getline(config, tmp);
	config >> min_order >> max_order >> cur_term_len;
	getline(config, tmp);
	getline(config, tmp);
	config >> PiPoint;
	ifstream fpoints("points.txt", ios::in);
	string s,tmp_s;
	for (int i = 0; i < num_points;i++)
	{
		getline(fpoints, s);
		points.push_back(s);
	}
	fpoints.close();
	ostringstream fname;
	st temp;
	bool flag;
	ifstream valueFile;
	double temp_val;
	st temp_st,final_st;
	for (int i = 0; i < num_points; i++)
	{
		cout << i << "\n";
		double factor;
		if(stof(points[i])-0.551>0)
			factor = 0.5;
		else
			factor = -0.5;
		res.clear();
		for (int j = min_order; j <= max_order; j++)
		{
			cout << "Order " << j << "\n";
			fname.str("");
			fname << "d:\\Andrew\\Practice\\!!!_Last Set\\Temp1\\5 SumNum Term\\5 SumNum Term\\results\\" << points[i] << "\\" << j << "_results_" << points[i] <<"_"<<cur_term_len<< ".txt";	
			
			ifstream cur(fname.str(), ios::in);
			
			while (!cur.eof())
			{
				getline(cur, s);
				if (s.length() > 0)
				{
					istringstream iss;
					iss.str(s);
					iss >> temp_st.name >> temp_val;

					decompose(temp_st);
					flag = false;
					//if ((temp_st.len == 3) && (temp_st.ops[2] == 'z'))//заменяем 3-ий оператор
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.ops[1] = temp_st.ops[1];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.nums[1] = temp_st.nums[1];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*factor;;
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	int re = final_st.name.compare("Jzz0_8");
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor;
					//	else
					//		res.push_back(final_st);
					//}
					//if ((temp_st.len == 3) && (temp_st.ops[1] == 'z') && (temp_st.nums[2] < 9))//заменяем 2ой оператор
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.ops[1] = temp_st.ops[2];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.nums[1] = temp_st.nums[2];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*factor;
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	int re = final_st.name.compare("Jzz0_8");
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor;
					//	else
					//		res.push_back(final_st);
					//}
					//if ((temp_st.len == 3) && (temp_st.ops[1] == 'z') && (temp_st.ops[2] == 'z') && (temp_st.nums[1] > 8 || temp_st.nums[2]>8))//заменяем оба
					//{
					//	final_st.len = 1;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor);
					//	final_st.name = "Sz0";
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}

					//////// temp_st.len==4
					//if ((temp_st.len == 4) && (temp_st.ops[1] == 'z') && (temp_st.ops[2] == 'z') && (temp_st.nums[3] <= 8))//заменяем два средних
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.ops[1] = temp_st.ops[3];
					//	final_st.nums[1] = temp_st.nums[3];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor);
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}
					//if ((temp_st.len == 4) && (temp_st.ops[2] == 'z') && (temp_st.ops[3] == 'z') && (temp_st.nums[1] <= 8))//заменяем два средних
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.ops[1] = temp_st.ops[1];
					//	final_st.nums[1] = temp_st.nums[1];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor);
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}
					//if ((temp_st.len == 4) && (temp_st.ops[1] == 'z') && (temp_st.ops[3] == 'z') && (temp_st.nums[2] <= 8))//заменяем первый и последний
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.ops[1] = temp_st.ops[2];
					//	final_st.nums[1] = temp_st.nums[2];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor);
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}
					//if ((temp_st.len == 4) && (temp_st.ops[1] == 'z') && (temp_st.ops[2] == 'z') && (temp_st.ops[3] == 'z') && (temp_st.nums[1] > 8) && (temp_st.nums[2] >8) && (temp_st.nums[3] > 8))//заменяем два средних
					//{
					//	final_st.len = 1;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor*factor);
					//	final_st.name = "Sz0";
					//	
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}

					////// 5 terms to quadratic 
					//if ((temp_st.len == 5) && (temp_st.ops[1] == 'z') && (temp_st.ops[2] == 'z') && (temp_st.ops[3] == 'z') && (temp_st.nums[4] <= 8))//заменяем первый и последний
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.ops[1] = temp_st.ops[4];
					//	final_st.nums[1] = temp_st.nums[4];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor*factor);
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}
					//
					//if ((temp_st.len == 5) && (temp_st.ops[1] == 'z') && (temp_st.ops[2] == 'z') && (temp_st.ops[4] == 'z') && (temp_st.nums[3] <= 8))//заменяем первый и последний
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.ops[1] = temp_st.ops[3];
					//	final_st.nums[1] = temp_st.nums[3];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor*factor);
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}

					//if ((temp_st.len == 5) && (temp_st.ops[1] == 'z') && (temp_st.ops[3] == 'z') && (temp_st.ops[4] == 'z') && (temp_st.nums[2] <= 8))//заменяем первый и последний
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.ops[1] = temp_st.ops[2];
					//	final_st.nums[1] = temp_st.nums[2];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor*factor);
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}
					//if ((temp_st.len == 5) && (temp_st.ops[2] == 'z') && (temp_st.ops[3] == 'z') && (temp_st.ops[4] == 'z') && (temp_st.nums[1] <= 8))//заменяем первый и последний
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.ops[1] = temp_st.ops[1];
					//	final_st.nums[1] = temp_st.nums[1];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor*factor);
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}
					//if ((temp_st.len == 5) && (temp_st.ops[1] == 'z') && (temp_st.ops[2] == 'z') && (temp_st.ops[3] == 'z') && (temp_st.ops[4] == 'z') && (temp_st.nums[1] > 8) && (temp_st.nums[2] > 8) && (temp_st.nums[3] > 8) && (temp_st.nums[4] > 8))//заменяем первый и последний
					//{
					//	final_st.len = 1;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor*factor);
					//	final_st.name = "S"+to_string(final_st.ops[0])+"0";
					//	//final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}
					

					//convert to qudratic term
					
					bool cur_condition;
					
					if (temp_st.len == cur_term_len&&temp_st.len>2)
					{
						for (int ii = 1; ii < cur_term_len; ii++)
						{
							cur_condition = true;
							for (int jj = 1; jj < cur_term_len; jj++)
							{
								if (jj == ii)
									cur_condition = cur_condition && (temp_st.nums[jj] <= 8);
								else
									cur_condition = cur_condition && (temp_st.ops[jj]=='z');
							}
							double f = 1;
							if (cur_condition)
							{
								for (int k = 1; k < cur_term_len - 1; k++)
									f *= factor;
								final_st.len = 2;
								final_st.ops[0] = temp_st.ops[0];
								final_st.nums[0] = temp_st.nums[0];
								final_st.ops[1] = temp_st.ops[ii];
								final_st.nums[1] = temp_st.nums[ii];
								for (int l = 1; l <= max_order; l++)
									final_st.value[l] = 0;
								final_st.value[j] = temp_val*f;
								final_st.name = "J";
								final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
								flag = true;
								vector<st>::iterator it = find(res.begin(), res.end(), final_st);
								if (it != res.end())
									it->value[j] += temp_val*f;
								else
									res.push_back(final_st);
							}
						}

					}
					//for sz
					double f = 1;
					if (temp_st.len == cur_term_len)
					{
						bool flag = (temp_st.nums[0]==0);
						for (int ii = 1; ii < cur_term_len; ii++)
						{
							if (temp_st.ops[ii] != 'z' || temp_st.nums[ii] <= 8)
							{
								flag = false;
								break;
							}							
						}
						if (flag)
						{
							for (int k = 1; k < cur_term_len - 1; k++)
								f *= factor;
							final_st.len = 1;
							final_st.ops[0] = temp_st.ops[0];
							final_st.nums[0] = 0;
							for (int l = 1; l <= max_order; l++)
								final_st.value[l] = 0;
							final_st.value[j] = temp_val*f;
							final_st.name = "S";
							final_st.name=final_st.name+ final_st.ops[0] + "0";
							vector<st>::iterator it = find(res.begin(), res.end(), final_st);
							if (it != res.end())
								it->value[j] += temp_val*f;
							else
								res.push_back(final_st);
						}

					}
					//for long-second terms
					bool flag = false;
					if (temp_st.len == cur_term_len && 2 == cur_term_len)
					{
						if (temp_st.nums[0] == 0 && temp_st.nums[1] > 8)
						{
							if (temp_st.ops[0] == 'p'&&temp_st.ops[1] == 'p')
								flag = true;
							if (temp_st.ops[0] == 'p'&&temp_st.ops[1] == 'm')
								flag = true;
							if (temp_st.ops[0] == 'm'&&temp_st.ops[1] == 'p')
								flag = true;
							if (temp_st.ops[0] == 'm'&&temp_st.ops[1] == 'm')
								flag = true;
							if (flag)
							{
								int find_flag=-1;
								for (int lll = 0; lll < long_res.size(); lll++)
								{
									if (long_res[lll].ops[0] == temp_st.ops[0] && long_res[lll].ops[1] == temp_st.ops[1])
									{
										find_flag = lll;
										break;
									}
								}

								if (find_flag != -1)
								{
									if ((temp_st.nums[1] != 14 && temp_st.nums[1] != 18 && temp_st.nums[1] != 22 && temp_st.nums[1] != 10) && (PiPoint == 1))
										long_res[find_flag].value[j] -= temp_val;
									else
										long_res[find_flag].value[j] += temp_val;
								}
								else
								{
									for (int l = 1; l <= max_order; l++)
										temp_st.value[l] = 0;
									if ((temp_st.nums[1] != 14 && temp_st.nums[1] != 18 && temp_st.nums[1] != 22 && temp_st.nums[1] != 10) && (PiPoint == 1))
										temp_st.value[j] = -temp_val;
									else
										temp_st.value[j] = temp_val;
									long_res.push_back(temp_st);
								}
									
							}
								
						}
					}
					//end long-second -terms
					//for CCC
					
					if (temp_st.len == cur_term_len&&temp_st.len>2)
					{
						flag = true;
						for (int ii = 0; ii < temp_st.len;ii++)
						{
							if (temp_st.ops[ii] != 'z')
							{
								flag = false;
								break;
							}
						}
						if (flag)
						{
							double f=1;
							for (int pp = 0; pp < temp_st.len; pp++)
								f *= factor;
							c_res.value[j] += temp_val * f / temp_st.len;
						}
					}

				}
			}

			cur.close();
			
		}
		fname.str("");
		if (cur_term_len!=2)
			fname << "res_" << points[i] << "_" << max_order << "_" << cur_term_len << ".txt";
		else
		{
			if (PiPoint==1)
				fname << "res_" << points[i] << "_" << max_order << "_" << cur_term_len <<"__(P,P).txt";
			else
				fname << "res_" << points[i] << "_" << max_order << "_" << cur_term_len <<"__(0,0).txt";
		}
		ofstream out(fname.str(), ios::out);
		out << "C" << cur_term_len<<"={";
		for (int k = 1; k <= max_order; k++)
		{
			out << c_res.value[k];
			if (k != max_order)
				out << ",";
		}
		out << "}\n";
		for (int j = 0; j < res.size(); j++)
		{
			//if (res[j].name[0] == 'S' || res[j].nums[1] <=2)
			if (res[j].name[0] == 'S' || res[j].nums[1] == 1|| res[j].nums[1] ==2)
			{
				out << res[j].name << "={";
				for (int k = 1; k <= max_order; k++)
				{
					out << res[j].value[k];
					if (k != max_order)
						out << ",";
				}
				out << "}\n";
			}

			
		}
		for (int j = 0; j < long_res.size(); j++)
		{
			out << "J" << long_res[j].ops[0] << long_res[j].ops[1] << "={";
			for (int k = 1; k <= max_order; k++)
			{
				out << long_res[j].value[k];
				if (k != max_order)
					out << ",";
			}

			out << "}\n";
		}

		out.close();
	}
	
	return 0;
}


///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// 9 Collect Third Terms.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
//#include <fstream>
//#include <iostream>
//#include <string>
//#include <vector>
//#include <sstream>
//#include <cmath>
//#include <algorithm>
//using namespace std;
//
//const string delim = "\\";
//const string out_res = "results";
//
//struct st
//{
//	string name;
//	double value;
//	bool operator==(st r)
//	{
//		if (name.compare(r.name) == 0)
//			return true;
//		else
//			return false;
//	};
//	/*bool short_compare(st r)
//	{
//	string n1, n2;
//	n1 = name.substr(0, name.length - 1);
//	n2 = r.name.substr(0, r.name.length - 1);
//	if (n1.compare(n2)==0)
//	return true;
//	else
//	}
//	};*/
//
//	vector<st> res;
//	int _tmain(int argc, _TCHAR* argv[])
//	{
//		vector<string> points;
//		ifstream config("config.txt", ios::in);
//		int num_points, order;
//		config >> num_points;
//		config >> order;
//		ifstream fpoints("points.txt", ios::in);
//		string s, tmp_s;
//		for (int i = 0; i < num_points; i++)
//		{
//			getline(fpoints, s);
//			points.push_back(s);
//		}
//		fpoints.close();
//		ostringstream fname;
//		st temp;
//		bool flag;
//		ifstream valueFile;
//		for (int i = 0; i < num_points; i++)
//		{
//			int factor;
//			double sz;
//			fname.str("");
//			fname << "d:\\results\\resumm\\s00\\sz0_" << order << "_" << points[i] << ".txt";
//			ifstream szfile(fname.str(), ios::in);
//			while (!szfile.eof())
//			{
//				szfile >> sz;
//			}
//			szfile.close();
//			if (sz > 0)
//				factor = -1;
//			else
//				factor = 1;
//			cout << factor << "\n";
//			fname.str("");
//			fname << points[i] << "_third_names.txt";
//			ifstream cur(fname.str(), ios::in);
//			res.clear();
//			while (!cur.eof())
//			{
//				getline(cur, s);
//				istringstream iss;
//				iss.str(s);
//				iss >> tmp_s;
//				flag = false;
//				if ((s[2] == 'z') && (s[3] != 'z'))
//				{
//					ifstream fn;
//					fname.str("");
//					fname << points[i] << "_third_names.txt";
//					temp.name = "J" + s[1] + s[3] + s[4] + s[6];
//					iss >> temp.value;
//					temp.value *= factor*0.5;
//					flag = true;
//					vector<st>::iterator it = find(res.begin(), res.end(), temp);
//					if (it != res.end())
//						it->value += temp.value;
//					else
//						res.push_back(temp);
//				}
//				if ((s[3] == 'z') && (s[2] != 'z'))
//				{
//					temp.name = "J" + s[1] + s[2] + s[4] + s[5];
//					iss >> temp.value;
//					temp.value *= factor*0.5;
//					flag = true;
//					vector<st>::iterator it = find(res.begin(), res.end(), temp);
//					if (it != res.end())
//						it->value += temp.value;
//					else
//						res.push_back(temp);
//				}
//			}
//
//			cur.close();
//			fname.str("");
//			fname << "res_" << points[i] << "_" << order << ".txt";
//			ofstream out(fname.str(), ios::out);
//			for (int j = 0; j < res.size(); j++)
//			{
//				out << res[j].name << " " << res[j].value;
//			}
//			out.close();
//		}
//
//		return 0;
//	}
//
//
//
//
//
