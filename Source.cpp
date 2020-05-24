#include "nlohmann/json.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>


using namespace std;
using json = nlohmann::json;

class cipher 
{
public:
	virtual void key_gen() = 0;
	virtual void encrypt() = 0;
	virtual void decrypt() = 0;
};

class replacement:public cipher
{
private:
	bool fileNOopen(string Path)
	{
		bool noOpen = false;
		ifstream file(Path);
		
		if (file.is_open()) 
		{
		
		}
		else 
		{
			noOpen = true;
		}
		
		file.close();
		return noOpen;
	}

public:
	void key_gen() override
	{
		string path_key;
		string path_alph;
		cout << "Enter the path to the file to save the key:" << "\t";
		cin >> path_key;
		cout << endl;
		if (path_key.find(".key") != -1)
		{
			cout << "Enter the path to the alphabet:" << "\t";
			cin >> path_alph;
			cout << endl;
			bool trig = 0;
			if (fileNOopen(path_alph))
			{
				trig = 1;
			}
			if (trig == 0)
			{
				ifstream file_alph(path_alph);
				json alph;
				file_alph >> alph;
				file_alph.close();
				if (alph.find("alph") != alph.end())
				{
					string array_alph;
					json data_a = alph.at("alph");
					json::iterator iter = data_a.begin();
					for (int i = 0; i < alph.at("alph").size(); i++)
					{
						string it = *iter;
						array_alph.push_back(it[0]);
						iter++;
					}

					string data;
					for (int i = 0; i < array_alph.size(); i++)
					{
						srand(time(NULL));
						int ran = rand() % 58 + 65;

						if (ran == 91 || ran == 92 || ran == 93 || ran == 94 || ran == 95 || ran == 96)
						{
							i--;
						}
						else
						{
							if (i != 0)
							{

								for (int j = 0; j < data.size(); j++)
								{

									if (data[j] == ran)
									{
										ran = rand() % 58 + 65;

										j = -1;
										continue;
									}
									if (ran == 91 || ran == 92 || ran == 93 || ran == 94 || ran == 95 || ran == 96)
									{
										ran = rand() % 58 + 65;

										j = -1;
									}

								}

								data.push_back(ran);
							}
							else
							{
								data.push_back(ran);
							}
						}
					}
					json key = { {"cipher type", "replacement"}, {"key",{}} };
					for (int i = 0; i < array_alph.size(); i++)
					{
						string sim1;
						string sim2;
						sim1.push_back(array_alph[i]);
						sim2.push_back(data[i]);
						key.at("key").push_back(json::array({ sim1,sim2 }));

					}
					ofstream key_file(path_key);
					if (key_file.is_open())
					{
						key_file << key;
						cout << "Key generated successfully" << endl;
					}
					else
					{
						cout << "ERROR" << endl;
					}
					key_file.close();
				}
				else
				{
					cout << "ERROR. The alphabet is set incorrectly" << endl;
				}
			}
			else
			{
				cout << "ERROR" << endl;
			}
		}
		else
		{
			cout << "ERROR. Check the path to the key" << endl;
		}
		
	}

	void encrypt() override
	{
		string path_key;
		string path_txt; 
		string path_cipher;
		cout << "Enter the path to the file with the key:" << "\t";
		cin >> path_key;
		cout << endl;
		if (path_key.find(".key") != -1)
		{

			bool trig = 0;
			if (fileNOopen(path_key))
			{
				trig == 1;
			}
			if (trig == 0)
			{
				ifstream file(path_key);
				json key;
				file >> key;
				file.close();
				if (key.find("cipher type").value() == "replacement")
				{
					cout << "Enter the path to the file to save the cipher:" << "\t";
					cin >> path_cipher;
					cout << endl;
					if (path_cipher.find(".encrypt") != -1)
					{
						cout << "Enter the path to the file with text:" << "\t";
						cin >> path_txt;
						cout << endl;
						if (fileNOopen(path_txt))
						{
							trig = 1;
						}
						if (trig == 0)
						{
							if (path_txt.find(".txt") != -1)
							{
								ofstream file_ciph(path_cipher);
								ifstream file_text(path_txt);
								if (file_text.is_open())
								{
									while (!file_text.eof())
									{
										string str1;
										getline(file_text, str1);
										for (int i = 0; i < str1.size(); i++)
										{
											string str2;
											str2.push_back(str1[i]);
											if (str2 != " ")
											{
												for (int j = 0; j < key.at("key").size(); j++)
												{
													if (str2 == key.at("key").at(j).at(0))
													{
														string keep;
														keep = key.at("key").at(j).at(1);
														str1[i] = keep[0];

														break;
													}
												}
											}

										}
										file_ciph << str1;
										file_ciph << endl;
									}

								}
								else
								{
									cout << "ERROR" << endl;
								}
							}
							else
							{
								cout << "ERROR. Check the path to the text" << endl;
							}
						}
						else
						{
							cout << "ERROR" << endl;
						}
					}
					else
					{
						cout << "ERROR. Check the path to the cipher" << endl;
					}
				}
				else
				{
					cout << "Incorrect encryption type" << endl;
				}
			}
			else
			{
				cout << "ERROR" << endl;
			}
		}
		else
		{
			cout << "ERROR. Check the path to the key" << endl;
		}
	}

	void decrypt() override
	{
		string path_key;
		string path_deciph;
		string path_cipher;
		cout << "Enter the path to the file with the key:" << "\t";
		cin >> path_key;
		cout << endl;
		if (path_key.find(".key") != -1)
		{
			bool trig = 0;
			if (fileNOopen(path_key))
			{
				trig = 1;
			}
			if (trig == 0)
			{
				ifstream file(path_key);
				json key;
				file >> key;
				file.close();
				if (key.find("cipher type").value() == "replacement")
				{
					cout << "Enter the path to the cipher file:" << "\t";
					cin >> path_cipher;
					cout << endl;
					if (fileNOopen(path_cipher))
					{
						trig = 1;
					}
					if (trig == 0)
					{
						if (path_cipher.find(".encrypt") != -1)
						{
							cout << "Enter the path to the file to save the text:" << "\t";
							cin >> path_deciph;
							cout << endl;
							if (path_deciph.find(".txt") != -1)
							{
								ofstream file_deciph(path_deciph);
								ifstream file_ciph(path_cipher);
								if (file_ciph.is_open())
								{
									while (!file_ciph.eof())
									{
										string str1;
										getline(file_ciph, str1);
										for (int i = 0; i < str1.size(); i++)
										{
											string str2;
											str2.push_back(str1[i]);
											if (str2 != " ")
											{
												for (int j = 0; j < key.at("key").size(); j++)
												{
													if (str2 == key.at("key").at(j).at(1))
													{
														string keep;
														keep = key.at("key").at(j).at(0);
														str1[i] = keep[0];

														break;
													}
												}
											}

										}
										file_deciph << str1;
										file_deciph << endl;
									}
								}
								else
								{
									cout << "ERROR" << endl;
								}
								file_deciph.close();
								file_ciph.close();
							}
							else
							{
								cout << "ERROR. Check the path to the text" << endl;
							}
						}
						else
						{
							cout << "ERROR. Check the path to the alphabet" << endl;
						}
					}
					else
					{
						cout << "ERROR" << endl;
					}
				}
				else
				{
					cout << "Incorrect encryption type" << endl;
				}
			}
			else
			{
				cout << "ERROR" << endl;
			}
		}
		else
		{
			cout << "ERROR. Check the path to the key" << endl;
		}
	}
};

class transposition : public cipher
{
private:
	bool fileNOopen(string Path)
	{
		bool noOpen = false;
		ifstream file(Path);

		if (file.is_open())
		{

		}
		else
		{
			noOpen = true;
		}

		file.close();
		return noOpen;
	}

public:
	void key_gen() override
	{
		string path_key;
		string path_txt;
		string path_alph;
		cout << "Enter the path to the file to save the key:" << "\t";
		cin >> path_key;
		cout << endl;
		if (path_key.find(".key") != -1)
		{
			cout << "Enter the path to the file with text:" << "\t";
			cin >> path_txt;
			cout << endl;
			bool trig = 0;
			if (fileNOopen(path_txt))
			{
				trig = 1;
			}
			if (trig == 0)
			{
				ofstream file_key(path_key);
				ifstream file_txt(path_txt);
				json key = { {"cipher type", "transposition"},{"key",{}} };
				int count = 0;
				int coun = 0;
				int keep;

				while (!file_txt.eof())
				{
					string str;
					string str1;
					string check;
					string word;

					file_txt >> str;


					vector<int>key_arr;
					int size = str.size();
					if (str.size() % 2 != 0)
					{
						size = str.size() - 1;
					}

					for (int i = 0; i < str.size(); i++)
					{
						key_arr.push_back(0);
					}
					if (size == 0)
					{
						continue;
					}
					for (int i = 0; i < size / 2; i++)
					{
						srand(time(NULL));
						int ran = rand() % str.size() + 1;
						if (ran != i + 1)
						{
							if (i != 0)
							{
								bool num = 0;
								for (int j = 0; j < key_arr.size(); j++)
								{
									if (ran == key_arr[j])
									{
										num = 1;
										i--;
										break;
									}
								}
								if (num == 1)
								{
									continue;
								}
								bool che = 0;
								for (int j = 0; j < key_arr.size(); j++)
								{
									if (str.size() % 2 == 0)
									{
										if (key_arr[j] == 0 && j + 1 != ran)
										{
											key_arr[j] = ran;
											key_arr[ran - 1] = j + 1;
											break;
										}
										else if (key_arr[j] == 0 && j + 1 == ran)
										{
											che = 1;
											i--;
											break;
										}
									}
									else
									{
										if (key_arr[j] == 0 && j + 1 != ran)
										{
											key_arr[j] = ran;
											key_arr[ran - 1] = j + 1;
											break;
										}
										else if (key_arr[j] == 0 && j + 1 == ran)
										{
											che = 1;
											i--;
											break;
										}
									}
								}
								if (che = 1)
								{
									continue;
								}
							}
							else
							{

								key_arr[0] = ran;
								key_arr[ran - 1] = 1;

							}
						}
						else
						{
							i--;
							continue;
						}
					}

					key.at("key").push_back(key_arr);
				}


				file_key << key;
				file_key.close();
				file_txt.close();

			}
			else
			{
				cout << "ERROR" << endl;
			}
			
		}
		else
		{
			cout << "ERROR. Check the path to the key" << endl;
		}
	}

	void encrypt() override
	{
		string path_key;
		string path_txt;
		string path_alph;
		string path_cipher;
		cout << "Enter the path to the file with the key:" << "\t";
		cin >> path_key;
		cout << endl;
		if (path_key.find(".key") != -1)
		{
			bool trig = 0;
			if (fileNOopen(path_key))
			{
				trig = 1;
			}
			if (trig == 0)
			{
				ifstream file(path_key);
				json key;
				file >> key;
				file.close();
				if (key.find("cipher type").value() == "transposition")
				{

					cout << "Enter the path to the file to save the cipher:" << "\t";
					cin >> path_cipher;
					cout << endl;
					if (path_cipher.find(".encrypt") != -1)
					{
						cout << "Enter the path to the file with text:" << "\t";
						cin >> path_txt;
						cout << endl;
						if (path_txt.find(".txt") != -1)
						{
							
							if (fileNOopen(path_key))
							{
								trig = 1;
							}
							if (trig == 0)
							{
								ofstream file_ciph(path_cipher);
								ifstream file_text(path_txt);
								int counter = 0;
								while (!file_text.eof())
								{
									string str;
									string str2;
									string space = " ";

									int count = 0;
									int coun = 0;
									int keep;
									getline(file_text, str);
									str2 = str;
									if (str2 != "")
									{
										for (int i = 0; i < key.at("key").size(); i++)
										{
											i = counter;
											counter++;
											string str3;
											string str4;
											for (int j = 0; j < str2.size(); j++)
											{
												j = coun;
												if (str2[coun] != space[0])
												{
													str3.push_back(str2[coun]);
												}
												else
												{
													coun++;
													break;
												}
												coun++;
												keep = coun;
											}
											str4 = str3;

											for (int j = 0; j < str3.size(); j++)
											{

												int a = key.at("key").at(i).at(j);
												if (a == 0)
												{
													continue;
												}
												str3[j] = str4[a - 1];


											}
											for (int j = 0; j < str3.size(); j++)
											{

												str[count] = str3[j];


												count++;
											}
											count++;
											if (keep == str2.size())
											{
												break;
											}

										}
										file_ciph << str;
										file_ciph << endl;
									}
								}

								file_ciph.close();
								file_text.close();
							}
							else
							{
								cout << "ERROR. Check the path to the text" << endl;
							}
						}
						else
						{
							cout << "ERROR. Check the path to the text" << endl;
						}
					}
					else
					{
						cout << "ERROR. Check the path to the cipher" << endl;
					}
				}
				else
				{
					cout << "Incorrect encryption type" << endl;
				}
			}
			else
			{
				cout << "ERROR" << endl;
			}
		}
		else
		{
			cout << "ERROR. Check the path to the key" << endl;
		}
	}

	void decrypt() override
	{
		string path_key;
		string path_alph;
		string path_cipher;
		string path_deciph;
		cout << "Enter the path to the file with the key:" << "\t";
		cin >> path_key;
		cout << endl;
		if (path_key.find(".key") != -1)
		{
			bool trig = 0;
			if (fileNOopen(path_key))
			{
				trig = 1;
			}
			
			if (trig == 0)
			{
				bool file_open = 1;
				ifstream file(path_key);
				json key;
				file >> key;
				file.close();
				if (key.find("cipher type").value() == "transposition")
				{

					cout << "Enter the path to the cipher file:" << "\t";
					cin >> path_cipher;
					cout << endl;
					if(fileNOopen(path_cipher))
					{
						trig = 1;
					}
					if (trig == 0)
					{
						if (path_cipher.find(".encrypt") != -1)
						{
							cout << "Enter the path to the file to save the text:" << "\t";
							cin >> path_deciph;
							cout << endl;
							if (path_deciph.find(".txt") != -1)
							{
								ofstream file_deciph(path_deciph);
								ifstream file_ciph(path_cipher);
								int counter = 0;
								while (!file_ciph.eof())
								{
									string str;
									string str2;
									string space = " ";
									int count = 0;
									int coun = 0;
									int keep;
									getline(file_ciph, str);
									str2 = str;
									if (str2 != "")
									{
										for (int i = 0; i < key.at("key").size(); i++)
										{
											i = counter;
											counter++;
											string str3;
											string str4;
											for (int j = 0; j < str2.size(); j++)
											{
												j = coun;
												if (str2[coun] != space[0])
												{
													str3.push_back(str2[coun]);
												}
												else
												{
													coun++;
													break;
												}
												coun++;
												keep = coun;
											}
											str4 = str3;
											for (int j = 0; j < str3.size(); j++)
											{
												int a = key.at("key").at(i).at(j);
												if (a == 0)
												{
													continue;;
												}
												str3[j] = str4[a - 1];
											}
											for (int j = 0; j < str3.size(); j++)
											{
												str[count] = str3[j];
												count++;
											}
											count++;
											if (keep == str2.size())
											{
												break;
											}
										}
										file_deciph << str;
										file_deciph << endl;
									}
								}
								file_deciph.close();
								file_ciph.close();
							}
							else
							{
								cout << "ERROR. Check the path to the text" << endl;
							}
						}
						else
						{
							cout << "ERROR. Check the path to the alphabet" << endl;
						}
					}
					else
					{
						cout << "ERROR" << endl;
					}




				}
				else
				{
					cout << "Incorrect encryptin type" << endl;
				}
			}
			else
			{
				cout << "ERROR" << endl;
			}
		}
		else
		{
			cout << "ERROR. Check the path to the key" << endl;
		}
	}
};

class gamming : public cipher
{
private:
	bool fileNOopen(string Path)
	{
		bool noOpen = false;
		ifstream file(Path);

		if (file.is_open())
		{

		}
		else
		{
			noOpen = true;
		}

		file.close();
		return noOpen;
	}

public:
	void key_gen() override
	{
		string path_key;
		string path_alph;
		cout << "Enter the path to the file to save the key:" << "\t";
		cin >> path_key;
		cout << endl;
		if (path_key.find(".key") != -1)
		{
			cout << "Enter the path to the alphabet:" << "\t";
			cin >> path_alph;
			cout << endl;
			if (path_alph.find(".alph") != -1)
			{
				bool trig = 0;
				if (fileNOopen(path_alph))
				{
					trig = 1;
				}
				if (trig == 0)
				{
					ifstream file_alph(path_alph);
					json alph;
					file_alph >> alph;
					file_alph.close();
					if (alph.find("alph") != alph.end())
					{
						string array_alph;
						json data_a = alph.at("alph");
						json::iterator iter = data_a.begin();
						for (int i = 0; i < alph.at("alph").size(); i++)
						{
							string it = *iter;
							array_alph.push_back(it[0]);
							iter++;
						}
						
						string data;
						for (int i = 0; i < array_alph.size(); i++)
						{
							srand(time(NULL));
							int ran = rand() % 58 + 65;

							if (ran == 91 || ran == 92 || ran == 93 || ran == 94 || ran == 95 || ran == 96)
							{
								i--;
							}
							else
							{
								if (i != 0)
								{

									for (int j = 0; j < data.size(); j++)
									{

										if (data[j] == ran)
										{
											ran = rand() % 58 + 65;

											j = -1;
											continue;
										}
										if (ran == 91 || ran == 92 || ran == 93 || ran == 94 || ran == 95 || ran == 96)
										{
											ran = rand() % 58 + 65;

											j = -1;
										}

									}

									data.push_back(ran);
								}
								else
								{
									data.push_back(ran);
								}
							}
						}
						json key = { {"cipher type", "gamming"}, {"key",{}} };
						for (int i = 0; i < array_alph.size(); i++)
						{
							string sim1;
							string sim2;
							sim1.push_back(array_alph[i]);
							sim2.push_back(data[i]);
							key.at("key").push_back(json::array({ sim1,sim2 }));

						}
						ofstream key_file(path_key);
						if (key_file.is_open())
						{
							key_file << key;
							cout << "Key generated successfully" << endl;
						}
						else
						{
							cout << "ERROR" << endl;
						}
						key_file.close();
					}
					else
					{
						cout << "ERROR. The alphabet is set incorrectly" << endl;
					}
				}
				else
				{
					cout << "ERROR" << endl;
				}
			}
			else
			{
				cout << "ERROR. Check the path to the alphabet" << endl;
			}


		}
		else
		{
			cout << "ERROR. Check the path to the key" << endl;
		}

	}

	void encrypt() override
	{
		string path_key;
		string path_txt;
		string path_cipher;
		cout << "Enter the path to the file with the key:" << "\t";
		cin >> path_key;
		cout << endl;
		if (path_key.find(".key") != -1)
		{
			bool trig = 0;
			if (fileNOopen(path_key))
			{
				trig = 1;
			}

			if (trig == 0)
			{

				ifstream file(path_key);
				json key;
				file >> key;
				file.close();
				if (key.find("cipher type").value() == "gamming")
				{
					cout << "Enter the path to the file to save the cipher:" << "\t";
					cin >> path_cipher;
					cout << endl;
					if (path_cipher.find(".encrypt") != -1)
					{
						cout << "Enter the path to the file with text:" << "\t";
						cin >> path_txt;
						cout << endl;
						if (path_txt.find(".txt") != -1)
						{
							if (fileNOopen(path_txt))
							{
								trig = 1;
							}
							if (trig == 0)
							{
								ofstream file_ciph(path_cipher);
								ifstream file_text(path_txt);
								while (!file_text.eof())
								{
									string str;
									getline(file_text, str);
									for (int i = 0; i < str.size(); i++)
									{
										string sim;
										int txt_sim;
										sim.push_back(str[i]);
										int count;

										for (int j = 0; j < key.at("key").size(); j++)
										{
											count = j;
											if (sim == key.at("key").at(j).at(0))
											{
												txt_sim = j;
												break;
											}

										}
										int key_sim;
										if (sim == key.at("key").at(count).at(0))
										{
											string sim2;
											if (i >= key.at("key").size())
											{
												int idx = i % key.at("key").size();
												sim2 = key.at("key").at(idx).at(1);
												for (int j = 0; j < key.at("key").size(); j++)
												{
													if (sim2 == key.at("key").at(j).at(0))
													{
														key_sim = j;
														break;
													}
												}

											}
											else
											{
												sim2 = key.at("key").at(i).at(1);
												for (int j = 0; j < key.at("key").size(); j++)
												{
													if (sim2 == key.at("key").at(j).at(0))
													{
														key_sim = j;
														break;
													}
												}
											}
											int summa = key_sim + txt_sim;
											int position = summa % key.at("key").size();
											string code_sim = key.at("key").at(position).at(0);
											str[i] = code_sim[0];
										}

									}
									file_ciph << str;
									file_ciph << endl;

								}

								file_ciph.close();
								file_text.close();
							}
							else
							{
								cout << "ERROR" << endl;
							}
						}
						else
						{
							cout << "ERROR. Check the path to the text" << endl;
						}
					}
					else
					{
						cout << "ERROR. Check the path to the cipher" << endl;
					}
				}
				else
				{
					cout << "Incorrect encryption type" << endl;
				}
			}
			else
			{
				cout << "ERROR" << endl;
			}
		}
		else
		{
			cout << "ERROR. Check the path to the key" << endl;
		}
	}

	void decrypt() override
	{
		string path_key;
		string path_deciph;
		string path_cipher;
		cout << "Enter the path to the file with the key:" << "\t";
		cin >> path_key;
		cout << endl;
		if (path_key.find(".key") != -1)
		{
			bool trig = 0;
			if (fileNOopen(path_key))
			{
				trig = 1;
			}
			if (trig == 0)
			{
				ifstream file(path_key);
				json key;
				file >> key;
				file.close();
				if (key.find("cipher type").value() == "gamming")
				{
					cout << "Enter the path to the file with the cipher:" << "\t";
					cin >> path_cipher;
					cout << endl;
					if (path_cipher.find(".encrypt") != -1)
					{
						if (fileNOopen(path_cipher))
						{
							trig = 1;
						}
						if (trig == 0)
						{
							cout << "Enter the path to the file to save the text:" << "\t";
							cin >> path_deciph;
							cout << endl;
							if (path_deciph.find(".txt") != -1)
							{
								ofstream file_deciph(path_deciph);
								ifstream file_ciph(path_cipher);

								while (!file_ciph.eof())
								{
									string str;
									getline(file_ciph, str);
									for (int i = 0; i < str.size(); i++)
									{
										string sim;
										int ciph_sim;
										sim.push_back(str[i]);
										int count;
										for (int j = 0; j < key.at("key").size(); j++)
										{
											count = j;
											if (sim == key.at("key").at(j).at(0))
											{
												ciph_sim = j;
												break;
											}

										}
										int key_sim;
										if (sim == key.at("key").at(count).at(0))
										{
											string sim2;
											if (i >= key.at("key").size())
											{
												int idx = i % key.at("key").size();
												sim2 = key.at("key").at(idx).at(1);
												for (int j = 0; j < key.at("key").size(); j++)
												{
													if (sim2 == key.at("key").at(j).at(0))
													{
														key_sim = j;
														break;
													}
												}

											}
											else
											{
												sim2 = key.at("key").at(i).at(1);
												for (int j = 0; j < key.at("key").size(); j++)
												{
													if (sim2 == key.at("key").at(j).at(0))
													{
														key_sim = j;
														break;
													}
												}
											}
											int summa = key.at("key").size() + ciph_sim - key_sim;
											int position = summa % key.at("key").size();
											string code_sim = key.at("key").at(position).at(0);
											str[i] = code_sim[0];
										}
									}
									file_deciph << str;
									file_deciph << endl;
								}
								file_deciph.close();
								file_ciph.close();
							}
							else
							{
								cout << "ERROR. Check the path to the text" << endl;
							}
						}
					}
					else
					{
						cout << "ERROR. Check the path to the alphabet" << endl;
					}
						
					
				}
				else
				{
					cout << "Incorrect encryption type" << endl;
				}
			}
			else
			{
				cout << "ERROR" << endl;
			}
		}
		else
		{
			cout << "ERROR. Check the path to the key" << endl;
		}
	}
};

int main()
{
	int a;
	cout << "Main menu" << endl;
	cout << "1)Encrypt/Decrypt" << endl << "2)Key generation" << endl;
	cin >> a;
	if (a == 1)
	{
		cout << "1)Encrypt" << endl << "2)Decrypt" << endl;
		cin >> a;
		if (a == 1)
		{
			cout << "Choose encryption type" << endl;
			cout << "1)replacement cipher" << endl << "2)transposition cipher" << endl << "3)gamming" << endl;
			cin >> a;
			if (a == 1)
			{
				replacement x;

				x.encrypt();
			}
			else if (a == 2)
			{
				transposition x;
				x.encrypt();
			}
			else if (a == 3)
			{
				gamming x;
				x.encrypt();
			}
			else if (a != 1 && a != 2 && a != 3)
			{
				cout << "Incorrect option" << endl;
			}
		}
		else if (a == 2)
		{
			cout << "Choose decryption rype" << endl;
			cout << "1)replacement cipher" << endl << "2)transposition cipher" << endl << "3)gamming" << endl;
			cin >> a;
			if (a == 1)
			{
				replacement x;
				x.decrypt();
			}
			else if (a == 2)
			{
				transposition x;
				x.decrypt();
			}
			else if (a == 3)
			{
				gamming x;
				x.decrypt();
			}
			else if (a != 1 && a != 2 && a != 3)
			{
				cout << "Incorrect option" << endl;
			}
		}
		else if (a != 1 && a != 2)
		{
			cout << "Incorrect option" << endl;
		}
	}
	else if (a == 2)
	{
		cout << "Choose type" << endl;
		cout << "1)replacement cipher" << endl << "2)transposition cipher" << endl << "3)gamming" << endl;
		cin >> a;
		if (a == 1)
		{
			replacement x;
			
			x.key_gen();
		}
		else if (a == 2)
		{
			transposition x;
			x.key_gen();
		}
		else if (a == 3)
		{
			gamming x;
			x.key_gen();
		}
		else if (a != 1 && a != 2 && a != 3)
		{
			cout << "Incorrect option" << endl;
		}
	}
	else if (a != 1 && a != 2)
	{
		cout << "Incorrect option" << endl;
	}


	system("pause");
	return 0;
}


//#include <iostream>
//#include <fstream>
//#include <ctime>
//#include "nlohmann/json.hpp"
//using namespace std;
//using json = nlohmann::json;
//class cipher {
//public:
//	virtual void key_generator(string path_save_file) = 0;
//	virtual void Encrypt(string path_save_file, string path_key, string path_txt) = 0;
//	virtual void decipher(string path_key, string path_encrypt, string path_save_file) = 0;
//};
//
//class replacement : public cipher { 
//private:
//	bool FileIsExist(string filePath)
//	{
//		bool isExist = false;
//		ifstream fin(filePath);
//
//		if (fin.is_open()) {
//
//		}
//		else {
//			isExist = true;
//		}
//
//		fin.close();
//		return isExist;
//	}
//	int black_list_check(string bl, int chack, string alph) {
//		bool trriger_bl = 0;
//		bool trriger_al = 0;
//		for (int i = 0; i < bl.size(); i++) {
//			if (bl[i] == chack) {
//				trriger_bl = 1;
//				break;
//			}
//		}
//		for (int i = 0; i < alph.size(); i++) {
//			if (alph[i] == chack) {
//				trriger_al = 1;
//				break;
//			}
//		}
//
//
//		if (trriger_al == 1) {
//			if (trriger_bl == 0) {
//				return chack;
//
//			}
//			else if (trriger_bl == 1) {
//				int back_or_front = rand() % 2;
//				if (back_or_front == 0) {
//					for (int i = 0; i < alph.size(); i++) {
//						bool trriger_win = 0;
//						for (int j = 0; j < bl.size(); j++) {
//							if (bl[j] == alph[i]) {
//								trriger_win = 1;
//								break;
//							}
//						}
//
//						if (trriger_win == 0) {
//							int res = alph[i];
//							return res;
//						}
//
//					}
//				}
//				if (back_or_front == 1) {
//					for (int i = alph.size() - 1; i >= 0; i--) {
//						bool trriger_win = 0;
//						for (int j = 0; j < bl.size(); j++) {
//							if (bl[j] == alph[i]) {
//								trriger_win = 1;
//								break;
//							}
//						}
//
//						if (trriger_win == 0) {
//							int res = alph[i];
//							return res;
//						}
//
//					}
//				}
//			}
//		}
//		else if (trriger_al == 0) {
//			int back_or_front = rand() % 2;
//			if (back_or_front == 0) {
//				for (int i = 0; i < alph.size(); i++) {
//					bool trriger_win = 0;
//					for (int j = 0; j < bl.size(); j++) {
//						if (bl[j] == alph[i]) {
//							trriger_win = 1;
//							break;
//						}
//					}
//
//					if (trriger_win == 0) {
//						int res = alph[i];
//						return res;
//					}
//
//				}
//			}
//			if (back_or_front == 1) {
//				for (int i = alph.size() - 1; i >= 0; i--) {
//					bool trriger_win = 0;
//					for (int j = 0; j < bl.size(); j++) {
//						if (bl[j] == alph[i]) {
//							trriger_win = 1;
//							break;
//						}
//					}
//
//					if (trriger_win == 0) {
//						int res = alph[i];
//						return res;
//					}
//
//				}
//			}
//		}
//
//	
//	}
//public:
//	void key_generator(string path_save_file) {
//		bool trriger = 0;
//		string path_alph;
//		cout << "Enter the path to the alphabet(.alph): "; cin >> path_alph; cout << endl;
//		if (path_alph.substr(path_alph.find_last_of(".") + 1) != "alph") {
//			trriger = 1;
//		}
//		if (path_save_file.substr(path_save_file.find_last_of(".") + 1) != "key") {
//			trriger = 1;
//		}
//		if (FileIsExist(path_alph)) {
//			trriger = 1;
//		}
//		if (trriger == 0) {
//			ifstream alph_file(path_alph);
//			json alph;
//			alph_file >> alph;
//			alph_file.close();
//			auto array_alph = alph.find("alph");
//			if (array_alph != alph.end()) { 
//				json key = { {"alg_type", "replacement"},{"key",{}} };
//				
//				string alph_data_str;
//				json alph_data = alph.at("alph");
//
//				json::iterator it = alph_data.begin();
//				for (int i = 0; i < alph.at("alph").size(); i++) { 
//					string tt = *it;
//					alph_data_str.push_back(tt[0]);
//					it++;
//				}
//				string key_data;
//				string black_list = "";
//				srand(time(0));
//				for (int i = 0; i < alph_data_str.size(); i++) {
//					int key_int = rand() % 10;
//					int minus = key_int % 2;
//					if (minus == 0) {
//						int chek = alph_data_str[i] - key_int;
//						int res = black_list_check(black_list, chek, alph_data_str);
//						key_data.push_back(res);
//						black_list.push_back(res);
//
//					}
//					else {
//						int chek = alph_data_str[i] + key_int;
//						int res = black_list_check(black_list, chek, alph_data_str);
//						key_data.push_back(res);
//						black_list.push_back(res);
//
//
//					}
//				}
//				
//				for (int i = 0; i < alph_data_str.size(); i++) {
//					string aa;
//					string ee;
//					aa.push_back(alph_data_str[i]);
//					ee.push_back(key_data[i]);
//					key.at("key").push_back(json::array({ aa,ee }));
//				}
//				ofstream key_file(path_save_file);
//				key_file << key;
//				key_file.close();
//			}
//			else {
//				cout << "alph is not correct!" << endl;
//			}
//		}
//		else {
//			cout << "ERROR" << endl;
//		}
//	}
//
//	void Encrypt(string path_save_file, string path_key, string path_txt) {
//		bool trriger = 0;
//		if (path_key.substr(path_key.find_last_of(".") + 1) != "key") {
//			trriger = 1;
//		}
//		if (path_txt.substr(path_txt.find_last_of(".") + 1) != "txt") {
//			trriger = 1;
//		}
//		if (path_save_file.substr(path_save_file.find_last_of(".") + 1) != "encrypt") {
//			trriger = 1;
//		}
//		if (FileIsExist(path_key)) {
//			trriger = 1;
//		}
//		if (FileIsExist(path_txt)) {
//			trriger = 1;
//		}
//		if (trriger == 0) {
//			json key;
//			ifstream key_file(path_key);
//			key_file >> key;
//			key_file.close();
//
//			auto type = key.find("alg_type");
//			if (type.value() == "replacement") {
//				ifstream txt_file(path_txt);
//				if (txt_file.peek() != EOF)  
//				{
//					int key_size = key.at("key").size();
//					ofstream encrypt_file(path_save_file);
//					while (txt_file) {
//						string txt_str;
//						getline(txt_file, txt_str);
//						for (int i = 0; i < txt_str.size(); i++) {
//							string simvol;
//							simvol.push_back(txt_str[i]);
//							for (int j = 0; j < key_size; j++) {
//								if (simvol == key.at("key").at(j).at(0)) {
//									string simvol_1;
//									simvol_1 = key.at("key").at(j).at(1);
//									txt_str[i] = simvol_1[0];
//									break;
//								}
//
//							}
//						}
//						encrypt_file << txt_str;
//						encrypt_file << "\n";
//					}
//					encrypt_file.close();
//
//				}
//				else {
//					cout << "txt empty" << endl;
//				}
//				txt_file.close();
//			}
//			else {
//				cout << "not correct type" << endl;
//			}
//
//		}
//		else {
//			cout << "not correct file extension or file is not found" << endl;
//		}
//
//
//	}
//
//	void decipher(string path_key, string path_encrypt, string path_save_file) {
//		bool trriger = 0;
//		if (path_key.substr(path_key.find_last_of(".") + 1) != "key") {
//			trriger = 1;
//		}
//		if (path_save_file.substr(path_save_file.find_last_of(".") + 1) != "txt") {
//			trriger = 1;
//		}
//		if (path_encrypt.substr(path_encrypt.find_last_of(".") + 1) != "encrypt") {
//			trriger = 1;
//		}
//		if (FileIsExist(path_key)) {
//			trriger = 1;
//		}
//		if (FileIsExist(path_encrypt)) {
//			trriger = 1;
//		}
//		if (trriger == 0) {
//			json key;
//			ifstream key_file(path_key);
//			key_file >> key;
//			key_file.close();
//
//			auto type = key.find("alg_type");
//			if (type.value() == "replacement") {
//				ifstream encrypt_file(path_encrypt);
//				if (encrypt_file.peek() != EOF)  
//				{
//					int key_size = key.at("key").size();
//					ofstream txt_file(path_save_file);
//					while (encrypt_file) {
//						string encrypt_str;
//						getline(encrypt_file, encrypt_str);
//						for (int i = 0; i < encrypt_str.size(); i++) {
//							string simvol;
//							simvol.push_back(encrypt_str[i]);
//							for (int j = 0; j < key_size; j++) {
//								if (simvol == key.at("key").at(j).at(1)) {
//									string simvol_1;
//									simvol_1 = key.at("key").at(j).at(0);
//									encrypt_str[i] = simvol_1[0];
//									break;
//								}
//
//							}
//						}
//						txt_file << encrypt_str;
//						txt_file << "\n";
//					}
//					txt_file.close();
//				}
//				else {
//					cout << "encrypt empty" << endl;
//				}
//				encrypt_file.close();
//			}
//			else {
//				cout << "not correct type" << endl;
//			}
//
//
//
//
//
//
//
//		}
//		else {
//			cout << "not correct file extension or file is not found" << endl;
//		}
//
//	}
//
//};
//
//class permutation : public cipher { 
//private:
//	int blak_list_f(string BB, int key_sm, string alph, int val) {
//		int minus = key_sm % 2;
//		char test;
//		int key_sm_2 = 0 - key_sm;
//		if (minus == 0) {
//			test = alph[val] + key_sm;
//		}
//		else {
//
//
//			test = alph[val] + key_sm_2;
//		}
//		bool bb_trriger = 0;
//		bool alph_trriger = 0;
//		for (int i = 0; i < alph.size(); i++) {
//			if (test == alph[i]) {
//				alph_trriger = 1;
//			}
//		}
//		for (int i = 0; i < BB.size(); i++) {
//			if (test == BB[i]) {
//				bb_trriger = 1;
//			}
//		}
//
//		if (bb_trriger == 0 && alph_trriger == 1) {
//			if (minus == 0) {
//				return key_sm;
//			}
//			else {
//				return key_sm_2;
//			}
//		}
//		else {
//			test = 126;
//			for (int i = 0; i < 40; i++) {
//				bb_trriger = 0;
//				int rr = rand() % alph.size();
//				for (int j = 0; j < BB.size(); j++) {
//					if (BB[j] == alph[rr]) {
//						bb_trriger = 1;
//						break;
//					}
//				}
//				if (bb_trriger == 0) {
//					test = alph[rr];
//					break;
//				}
//			}
//			if (test == 126) {
//				for (int i = 0; i < alph.size(); i++) {
//					bb_trriger = 0;
//					for (int j = 0; j < BB.size(); j++) {
//						if (alph[i] == BB[j]) {
//							bb_trriger = 1;
//							break;
//						}
//					}
//					if (bb_trriger == 0) {
//						test = alph[i];
//						break;
//					}
//
//				}
//
//
//			}
//
//			int test_int = test;
//			int alph_int = alph[val];
//			int val_1 = alph_int - test_int;
//
//			
//			val_1 = 0 - val_1;
//
//			return val_1;
//			
//
//
//
//
//		}
//
//
//
//
//
//
//	}
//	bool FileIsExist(string filePath)
//	{
//		bool isExist = false;
//		ifstream fin(filePath);
//
//		if (fin.is_open()) {
//
//		}
//		else {
//			isExist = true;
//		}
//
//		fin.close();
//		return isExist;
//	}
//public:
//	void key_generator(string path_save_file) {
//		bool trriger = 0;
//
//
//
//		if (path_save_file.substr(path_save_file.find_last_of(".") + 1) != "key") {
//			trriger = 1;
//		}
//
//		if (trriger == 0) {
//			int key_size;
//			cout << "Enter the key size: "; cin >> key_size; cout << endl;
//			if (key_size > 0) {
//				json key = { {"alg_type", "permutation"},{"key",{}} };
//				int* key_int = new int[key_size];
//
//				srand(time(0));
//				for (int i = 0; i < key_size; i++) {
//					bool trriger = 0;
//					for (int j = 0; j < key_size + 100; j++) {
//						trriger = 0;
//						int nam = rand() % key_size + 1;
//						for (int k = 0; k < key_size; k++) {
//							if (key_int[k] == nam) {
//								trriger = 1;
//							}
//						}
//						if (trriger == 0) {
//							key_int[i] = nam;
//							break;
//						}
//					}
//					if (trriger == 1) {
//						for (int j = 0; j < key_size; j++) {
//							trriger = 0;
//							int nam = j + 1;
//							for (int k = 0; k < key_size; k++) {
//								if (nam == key_int[k]) {
//									trriger = 1;
//								}
//							}
//							if (trriger == 0) {
//								key_int[i] = nam;
//								break;
//							}
//						}
//					}
//
//				}
//				for (int i = 0; i < key_size; i++) {
//
//					key.at("key").push_back(key_int[i]);
//
//				}
//				ofstream key_file(path_save_file);
//				key_file << key;
//				key_file.close();
//
//
//				delete[]key_int;
//			}
//			else {
//				cout << "Size is not correct" << endl;
//			}
//
//		}
//		else {
//			cout << "not correct file extension or file is not found" << endl;
//		}
//	}
//	void Encrypt(string path_save_file, string path_key, string path_txt) {
//		bool trriger = 0;
//		if (path_key.substr(path_key.find_last_of(".") + 1) != "key") {
//			trriger = 1;
//		}
//		if (path_txt.substr(path_txt.find_last_of(".") + 1) != "txt") {
//			trriger = 1;
//		}
//		if (path_save_file.substr(path_save_file.find_last_of(".") + 1) != "encrypt") {
//			trriger = 1;
//		}
//		if (FileIsExist(path_key)) {
//			trriger = 1;
//		}
//		if (FileIsExist(path_txt)) {
//			trriger = 1;
//		}
//		if (trriger == 0) {
//			json key;
//			ifstream key_file(path_key);
//			key_file >> key;
//			key_file.close();
//
//			auto type = key.find("alg_type");
//			if (type.value() == "permutation") {
//				ifstream txt_file(path_txt);
//				if (txt_file.peek() != EOF)  
//				{
//					int key_size = key.at("key").size();
//					ofstream encrypt_file(path_save_file);
//
//
//					while (txt_file) {
//						string txt_str;
//						string end;
//
//						getline(txt_file, txt_str);
//						int ff = txt_str.size() % key_size;
//						if (ff != 0) {
//							int rr = key_size - ff;
//							for (int i = 0; i < rr; i++) {
//								txt_str.push_back('#');
//							}
//						}
//						char* str_encrupt_ch = new char[txt_str.size()];
//						
//						ff = txt_str.size() / key_size;
//						int txt_elem = 0;
//						for (int i = 0; i < ff; i++) {
//							for (int j = 0; j < key_size; j++) {
//								int tt = key.at("key").at(j) - 1;
//
//								int iii = i * key_size;
//								str_encrupt_ch[tt + iii] = txt_str[txt_elem];
//								txt_elem++;
//
//							}
//
//
//						}
//
//						for (int i = 0; i < txt_str.size(); i++) {
//
//							end.push_back(str_encrupt_ch[i]);
//
//						}
//
//
//						delete[]str_encrupt_ch;
//						encrypt_file << end;
//						encrypt_file << "\n";
//					}
//
//
//
//
//
//
//					encrypt_file.close();
//				}
//				else {
//					cout << "txt empty" << endl;
//				}
//				txt_file.close();
//			}
//			else {
//				cout << "not correct type" << endl;
//			}
//
//		}
//		else {
//			cout << "not correct file extension or file is not found" << endl;
//		}
//
//	}
//	void decipher(string path_key, string path_encrypt, string path_save_file) {
//		bool trriger = 0;
//		if (path_key.substr(path_key.find_last_of(".") + 1) != "key") {
//			trriger = 1;
//		}
//		if (path_save_file.substr(path_save_file.find_last_of(".") + 1) != "txt") {
//			trriger = 1;
//		}
//		if (path_encrypt.substr(path_encrypt.find_last_of(".") + 1) != "encrypt") {
//			trriger = 1;
//		}
//		if (FileIsExist(path_key)) {
//			trriger = 1;
//		}
//		if (FileIsExist(path_encrypt)) {
//			trriger = 1;
//		}
//		if (trriger == 0) {
//			json key;
//			ifstream key_file(path_key);
//			key_file >> key;
//			key_file.close();
//
//			auto type = key.find("alg_type");
//			if (type.value() == "permutation") {
//				ifstream encrypt_file(path_encrypt);
//				if (encrypt_file.peek() != EOF)  
//				{
//					int key_size = key.at("key").size();
//					ofstream txt_file(path_save_file);
//
//					while (encrypt_file) {
//						string encrypt_str;
//						string end;
//						getline(encrypt_file, encrypt_str);
//						char* str_encrupt_ch = new char[encrypt_str.size()];
//
//						int ff = encrypt_str.size() / key_size;
//
//						for (int i = 0; i < ff; i++) {
//							for (int j = 0; j < key_size; j++) {
//								int tt = key.at("key").at(j) - 1;
//								int iii = i * key_size;
//								str_encrupt_ch[j + iii] = encrypt_str[iii + tt];
//
//							}
//
//
//						}
//
//						for (int i = 0; i < encrypt_str.size(); i++) {
//
//							end.push_back(str_encrupt_ch[i]);
//
//						}
//						int end_size = end.size();
//						for (int i = end_size - 1; i >= 0; i--) {
//							if (end[i] == '#') {
//								end.pop_back();
//							}
//							else {
//								break;
//							}
//
//						}
//
//
//
//
//
//
//
//						txt_file << end;
//						txt_file << "\n";
//					}
//
//					txt_file.close();
//				}
//				else {
//					cout << "encrypt empty" << endl;
//				}
//				encrypt_file.close();
//			}
//			else {
//				cout << "not correct type" << endl;
//			}
//
//		}
//		else {
//			cout << "not correct file extension or file is not found" << endl;
//		}
//
//	}
//};
//
//class gamming : public cipher { 
//private:
//	bool FileIsExist(string filePath)
//	{
//		bool isExist = false;
//		ifstream fin(filePath);
//
//		if (fin.is_open()) {
//
//		}
//		else {
//			isExist = true;
//		}
//
//		fin.close();
//		return isExist;
//	}
//	int black_list_check(string bl, int chack, string alph) {
//		bool trriger_bl = 0;
//		bool trriger_al = 0;
//		for (int i = 0; i < bl.size(); i++) {
//			if (bl[i] == chack) {
//				trriger_bl = 1;
//				break;
//			}
//		}
//		for (int i = 0; i < alph.size(); i++) {
//			if (alph[i] == chack) {
//				trriger_al = 1;
//				break;
//			}
//		}
//
//
//		if (trriger_al == 1) {
//			if (trriger_bl == 0) {
//				return chack;
//
//			}
//			else if (trriger_bl == 1) {
//				int back_or_front = rand() % 2;
//				if (back_or_front == 0) {
//					for (int i = 0; i < alph.size(); i++) {
//						bool trriger_win = 0;
//						for (int j = 0; j < bl.size(); j++) {
//							if (bl[j] == alph[i]) {
//								trriger_win = 1;
//								break;
//							}
//						}
//
//						if (trriger_win == 0) {
//							int res = alph[i];
//							return res;
//						}
//
//					}
//				}
//				if (back_or_front == 1) {
//					for (int i = alph.size() - 1; i >= 0; i--) {
//						bool trriger_win = 0;
//						for (int j = 0; j < bl.size(); j++) {
//							if (bl[j] == alph[i]) {
//								trriger_win = 1;
//								break;
//							}
//						}
//
//						if (trriger_win == 0) {
//							int res = alph[i];
//							return res;
//						}
//
//					}
//				}
//			}
//		}
//		else if (trriger_al == 0) {
//			int back_or_front = rand() % 2;
//			if (back_or_front == 0) {
//				for (int i = 0; i < alph.size(); i++) {
//					bool trriger_win = 0;
//					for (int j = 0; j < bl.size(); j++) {
//						if (bl[j] == alph[i]) {
//							trriger_win = 1;
//							break;
//						}
//					}
//
//					if (trriger_win == 0) {
//						int res = alph[i];
//						return res;
//					}
//
//				}
//			}
//			if (back_or_front == 1) {
//				for (int i = alph.size() - 1; i >= 0; i--) {
//					bool trriger_win = 0;
//					for (int j = 0; j < bl.size(); j++) {
//						if (bl[j] == alph[i]) {
//							trriger_win = 1;
//							break;
//						}
//					}
//
//					if (trriger_win == 0) {
//						int res = alph[i];
//						return res;
//					}
//
//				}
//			}
//		}
//
//
//	}
//public:
//	void key_generator(string path_save_file) {
//		bool trriger = 0;
//		string path_alph;
//		cout << "Enter the path to the alphabet(.alph): "; cin >> path_alph; cout << endl;
//		if (path_alph.substr(path_alph.find_last_of(".") + 1) != "alph") {
//			trriger = 1;
//		}
//		if (path_save_file.substr(path_save_file.find_last_of(".") + 1) != "key") {
//			trriger = 1;
//		}
//		if (FileIsExist(path_alph)) {
//			trriger = 1;
//		}
//		if (trriger == 0) {
//			ifstream alph_file(path_alph);
//			json alph;
//			alph_file >> alph;
//			alph_file.close();
//			auto array_alph = alph.find("alph");
//			if (array_alph != alph.end()) { 
//				json key = { {"alg_type", "gamming"},{"key",{}} };
//
//				string alph_data_str;
//				json alph_data = alph.at("alph");
//
//				json::iterator it = alph_data.begin();
//				for (int i = 0; i < alph.at("alph").size(); i++) { 
//					string tt = *it;
//					alph_data_str.push_back(tt[0]);
//					it++;
//				}
//				string key_data;
//				string black_list = "";
//				srand(time(0));
//				for (int i = 0; i < alph_data_str.size(); i++) {
//					int key_int = rand() % 10;
//					int minus = key_int % 2;
//					if (minus == 0) {
//						int chek = alph_data_str[i] - key_int;
//						int res = black_list_check(black_list, chek, alph_data_str);
//						key_data.push_back(res);
//						black_list.push_back(res);
//
//					}
//					else {
//						int chek = alph_data_str[i] + key_int;
//						int res = black_list_check(black_list, chek, alph_data_str);
//						key_data.push_back(res);
//						black_list.push_back(res);
//
//
//					}
//				}
//
//				for (int i = 0; i < alph_data_str.size(); i++) {
//					string aa;
//					string ee;
//					aa.push_back(alph_data_str[i]);
//					ee.push_back(key_data[i]);
//					key.at("key").push_back(json::array({ aa,ee }));
//				}
//				
//				ofstream key_file(path_save_file);
//				key_file << key;
//				key_file.close();
//			}
//			else {
//				cout << "alph is not correct!" << endl;
//			}
//		}
//		else {
//			cout << "ERROR" << endl;
//		}
//	}
//	void Encrypt(string path_save_file, string path_key, string path_txt) {
//		bool trriger = 0;
//		if (path_key.substr(path_key.find_last_of(".") + 1) != "key") {
//			trriger = 1;
//		}
//		if (path_txt.substr(path_txt.find_last_of(".") + 1) != "txt") {
//			trriger = 1;
//		}
//		if (path_save_file.substr(path_save_file.find_last_of(".") + 1) != "encrypt") {
//			trriger = 1;
//		}
//		if (FileIsExist(path_key)) {
//			trriger = 1;
//		}
//		if (FileIsExist(path_txt)) {
//			trriger = 1;
//		}
//		if (trriger == 0) {
//			json key;
//			ifstream key_file(path_key);
//			key_file >> key;
//			key_file.close();
//
//			auto type = key.find("alg_type");
//			if (type.value() == "gamming") {
//				ifstream txt_file(path_txt);
//				if (txt_file.peek() != EOF)  
//				{
//					int key_size = key.at("key").size();
//					ofstream encrypt_file(path_save_file);
//					while (txt_file) {
//						string txt_str;
//						getline(txt_file, txt_str);
//						for (int i = 0; i < txt_str.size(); i++) {
//							bool txt_trriger = 0;
//							string simvol;
//							simvol.push_back(txt_str[i]);
//							int where_txt_simvol;
//
//							for (int j = 0; j < key_size; j++) {
//								if (simvol == key.at("key").at(j).at(0)) {
//									where_txt_simvol = j;
//									txt_trriger = 1;
//									break;
//								}
//							}
//							if (txt_trriger == 1) {
//							
//								int where_key_simvol;
//
//								if (i >= key_size) {
//									int i_2 = i % key_size;
//									string simvol_key = key.at("key").at(i_2).at(1);
//
//									for (int j = 0; j < key_size; j++) {
//										if (simvol_key == key.at("key").at(j).at(0)) {
//											where_key_simvol = j;
//											break;
//										}
//									}
//								}
//								else {
//									string simvol_key = key.at("key").at(i).at(1);
//
//									for (int j = 0; j < key_size; j++) {
//										if (simvol_key == key.at("key").at(j).at(0)) {
//											where_key_simvol = j;
//											break;
//										}
//									}
//								}
//								int sum = where_key_simvol + where_txt_simvol;
//								int where_res = sum % key_size;
//								string res = key.at("key").at(where_res).at(0);
//								txt_str[i] = res[0];
//
//							}
//						}
//
//
//
//
//
//
//
//
//						encrypt_file << txt_str;
//						encrypt_file << "\n";
//					}
//
//					encrypt_file.close();
//
//				}
//				else {
//					cout << "txt empty" << endl;
//				}
//				txt_file.close();
//			}
//			else {
//				cout << "not correct type" << endl;
//			}
//
//		}
//		else {
//			cout << "not correct file extension or file is not found" << endl;
//		}
//
//
//
//
//	}
//	void decipher(string path_key, string path_encrypt, string path_save_file) {
//
//		bool trriger = 0;
//		if (path_key.substr(path_key.find_last_of(".") + 1) != "key") {
//			trriger = 1;
//		}
//		if (path_save_file.substr(path_save_file.find_last_of(".") + 1) != "txt") {
//			trriger = 1;
//		}
//		if (path_encrypt.substr(path_encrypt.find_last_of(".") + 1) != "encrypt") {
//			trriger = 1;
//		}
//		if (FileIsExist(path_key)) {
//			trriger = 1;
//		}
//		if (FileIsExist(path_encrypt)) {
//			trriger = 1;
//		}
//		if (trriger == 0) {
//			json key;
//			ifstream key_file(path_key);
//			key_file >> key;
//			key_file.close();
//
//			auto type = key.find("alg_type");
//			if (type.value() == "gamming") {
//				ifstream encrypt_file(path_encrypt);
//				if (encrypt_file.peek() != EOF)  
//				{
//					int key_size = key.at("key").size();
//					ofstream txt_file(path_save_file);
//					while (encrypt_file) {
//						string encrypt_str;
//						getline(encrypt_file, encrypt_str);
//						for (int i = 0; i < encrypt_str.size(); i++) {
//
//							bool encrypt_trriger = 0;
//							string simvol;
//							simvol.push_back(encrypt_str[i]);
//							int where_encrypt_simvol;
//
//							for (int j = 0; j < key_size; j++) {
//								if (simvol == key.at("key").at(j).at(0)) {
//									where_encrypt_simvol = j;
//									encrypt_trriger = 1;
//									break;
//								}
//							}
//							if (encrypt_trriger == 1) {
//								
//								int where_key_simvol;
//
//								if (i >= key_size) {
//									int i_2 = i % key_size;
//									string simvol_key = key.at("key").at(i_2).at(1);
//
//									for (int j = 0; j < key_size; j++) {
//										if (simvol_key == key.at("key").at(j).at(0)) {
//											where_key_simvol = j;
//											break;
//										}
//									}
//								}
//								else {
//									string simvol_key = key.at("key").at(i).at(1);
//
//									for (int j = 0; j < key_size; j++) {
//										if (simvol_key == key.at("key").at(j).at(0)) {
//											where_key_simvol = j;
//											break;
//										}
//									}
//								}
//
//
//								int sum = where_encrypt_simvol + key_size - where_key_simvol;
//								int where_res = sum % key_size;
//								string res = key.at("key").at(where_res).at(0);
//								encrypt_str[i] = res[0];
//
//							}
//
//
//
//
//
//
//						}
//						txt_file << encrypt_str;
//						txt_file << "\n";
//					}
//					txt_file.close();
//				}
//				else {
//					cout << "encrypt empty" << endl;
//				}
//				encrypt_file.close();
//			}
//			else {
//				cout << "not correct type" << endl;
//			}
//
//
//
//
//
//
//
//		}
//		else {
//			cout << "not correct file extension or file is not found" << endl;
//		}
//
//
//
//
//
//
//
//	}
//};
//
//int main() {
//
//	cout << "\tMain menu" << endl;
//	cout << "1) Encrypt/Decrypt" << endl;
//	cout << "2) Generate key" << endl;
//	int i;
//	cin >> i; cout << endl;
//	if (i == 1) {
//		i = 0;
//		cout << "\tEncrypt/Decrypt" << endl;
//		cout << "1) Encrypt" << endl;
//		cout << "2) Decrypt" << endl;
//		cin >> i;
//		if (i == 1) {
//			i = 0;
//			cout << "\tChoose type" << endl;
//			cout << "1) replacement cipher" << endl;
//			cout << "2) permutation cipher " << endl;
//			cout << "3) gamma encryption" << endl;
//			cin >> i; cout << endl;
//			if (i == 1) {
//				cout << "\t replacement cipher" << endl;
//				replacement a;
//				string path_txt;
//				string path_save_file;
//				string path_key;
//				cout << "Enter file path for encryption(.txt) :"; cin >> path_txt; cout << endl;
//				cout << "Enter the path to save the file(.encrypt) :"; cin >> path_save_file; cout << endl;
//				cout << "Enter key path(.key) :"; cin >> path_key; cout << endl;
//				a.Encrypt(path_save_file, path_key, path_txt);
//
//				fstream ff(path_save_file);
//				if (ff.is_open()) {
//					cout << "Finish" << endl;
//				}
//				else {
//					cout << "ERROR" << endl;
//				}
//				ff.close();
//
//
//			}
//			else if (i == 2) {
//				cout << "\t permutation cipher" << endl;
//				permutation a;
//				string path_txt;
//				string path_save_file;
//				string path_key;
//				cout << "Enter file path for encryption(.txt) : "; cin >> path_txt; cout << endl;
//				cout << "Enter the path to save the file(.encrypt)  "; cin >> path_save_file; cout << endl;
//				cout << "Enter key path(.key) : "; cin >> path_key; cout << endl;
//				a.Encrypt(path_save_file, path_key, path_txt);
//				fstream ff(path_save_file);
//				if (ff.is_open()) {
//					cout << "Finish" << endl;
//				}
//				else {
//					cout << "ERROR" << endl;
//				}
//				ff.close();
//
//
//			}
//			else if (i == 3) {
//				cout << "\t gamma encryption" << endl;
//				gamming a;
//				string path_txt;
//				string path_save_file;
//				string path_key;
//				cout << "Enter file path for encryption(.txt) : "; cin >> path_txt; cout << endl;
//				cout << "Enter the path to save the file(.encrypt)  "; cin >> path_save_file; cout << endl;
//				cout << "Enter key path(.key) : "; cin >> path_key; cout << endl;
//				a.Encrypt(path_save_file, path_key, path_txt);
//				fstream ff(path_save_file);
//				if (ff.is_open()) {
//					cout << "Finish" << endl;
//				}
//				else {
//					cout << "ERROR" << endl;
//				}
//				ff.close();
//
//
//
//			}
//
//
//		}
//		else if (i == 2) {
//			i = 0;
//			cout << "\tChoose type" << endl;
//			cout << "1) replacement cipher" << endl;
//			cout << "2) permutation cipher " << endl;
//			cout << "3) gamma encryption" << endl;
//			cin >> i; cout << endl;
//			if (i == 1) {
//				cout << "\t replacement cipher" << endl;
//				replacement a;
//				string path_encrupt;
//				string path_save_file;
//				string path_key;
//				cout << "Enter the path to the file to decrypt(.encrypt) :"; cin >> path_encrupt; cout << endl;
//				cout << "Enter the path to save the file(.txt) :"; cin >> path_save_file; cout << endl;
//				cout << "Enter key path(.key) :"; cin >> path_key; cout << endl;
//				a.decipher(path_key, path_encrupt, path_save_file);
//				fstream ff(path_save_file);
//				if (ff.is_open()) {
//					cout << "Finish" << endl;
//				}
//				else {
//					cout << "ERROR" << endl;
//				}
//				ff.close();
//			}
//			else if (i == 2) {
//				cout << "\t permutation cipher" << endl;
//				permutation a;
//				string path_encrupt;
//				string path_save_file;
//				string path_key;
//				cout << "Enter the path to the file to decrypt(.encrypt) :"; cin >> path_encrupt; cout << endl;
//				cout << "Enter the path to save the file(.txt) :"; cin >> path_save_file; cout << endl;
//				cout << "Enter key path(.key) :"; cin >> path_key; cout << endl;
//				a.decipher(path_key, path_encrupt, path_save_file);
//				fstream ff(path_save_file);
//				if (ff.is_open()) {
//					cout << "Finish" << endl;
//				}
//				else {
//					cout << "ERROR" << endl;
//				}
//				ff.close();
//
//			}
//			else if (i == 3) {
//				cout << "\t gamma encryption" << endl;
//				gamming a;
//				string path_encrupt;
//				string path_save_file;
//				string path_key;
//				cout << "Enter the path to the file to decrypt(.encrypt) :"; cin >> path_encrupt; cout << endl;
//				cout << "Enter the path to save the file(.txt) :"; cin >> path_save_file; cout << endl;
//				cout << "Enter key path(.key) :"; cin >> path_key; cout << endl;
//				a.decipher(path_key, path_encrupt, path_save_file);
//				fstream ff(path_save_file);
//				if (ff.is_open()) {
//					cout << "Finish" << endl;
//				}
//				else {
//					cout << "ERROR" << endl;
//				}
//				ff.close();
//
//
//
//			}
//
//		}
//
//	}
//	else if (i == 2) {
//		i = 0;
//		cout << "\tGenerate key" << endl;
//		cout << "1) replacement cipher" << endl;
//		cout << "2) permutation cipher " << endl;
//		cout << "3) gamma encryption" << endl;
//		cin >> i; cout << endl;
//		if (i == 1) {
//			cout << "\t replacement cipher" << endl;
//			replacement a;
//
//			string path_save_file;
//
//			cout << "Enter the path to save key file(.key): "; cin >> path_save_file; cout << endl;
//			a.key_generator(path_save_file);
//			fstream ff(path_save_file);
//			if (ff.is_open()) {
//				cout << "Finish" << endl;
//			}
//			else {
//				cout << "ERROR" << endl;
//			}
//			ff.close();
//		}
//		else if (i == 2) {
//			cout << "\t permutation cipher" << endl;
//			permutation a;
//
//			string path_save_file;
//
//			cout << "Enter the path to save key file(.key): "; cin >> path_save_file; cout << endl;
//			a.key_generator(path_save_file);
//			fstream ff(path_save_file);
//			if (ff.is_open()) {
//				cout << "Finish" << endl;
//			}
//			else {
//				cout << "ERROR" << endl;
//			}
//			ff.close();
//
//
//		}
//		else if (i == 3) {
//			cout << "\t gamma encryption" << endl;
//			gamming a;
//
//			string path_save_file;
//
//			cout << "Enter the path to save key file(.key): "; cin >> path_save_file; cout << endl;
//			a.key_generator(path_save_file);
//			fstream ff(path_save_file);
//			if (ff.is_open()) {
//				cout << "Finish" << endl;
//			}
//			else {
//				cout << "ERROR" << endl;
//			}
//			ff.close();
//
//
//
//		}
//
//
//	}
//
//
//
//
//
//
//	system("pause");
//	return 0;
//}


//bool trriger = 0;
//		string path_alph;
//		cout << "Enter the path to the alphabet(.alph): "; cin >> path_alph; cout << endl;
//		if (path_alph.substr(path_alph.find_last_of(".") + 1) != "alph") {
//			trriger = 1;
//		}
//		if (path_save_file.substr(path_save_file.find_last_of(".") + 1) != "key") {
//			trriger = 1;
//		}
//		if (FileIsExist(path_alph)) {
//			trriger = 1;
//		}
//		if (trriger == 0) {
//			ifstream alph_file(path_alph);
//			json alph;
//			alph_file >> alph;
//			alph_file.close();
//			auto array_alph = alph.find("alph");
//			if (array_alph != alph.end()) { 
//				json key = { {"alg_type", "replacement"},{"key",{}} };
//				
//				string alph_data_str;
//				json alph_data = alph.at("alph");
//
//				json::iterator it = alph_data.begin();
//				for (int i = 0; i < alph.at("alph").size(); i++) { 
//					string tt = *it;
//					alph_data_str.push_back(tt[0]);
//					it++;
//				}
//				string key_data;
//				string black_list = "";
//				srand(time(0));
//				for (int i = 0; i < alph_data_str.size(); i++) {
//					int key_int = rand() % 10;
//					int minus = key_int % 2;
//					if (minus == 0) {
//						int chek = alph_data_str[i] - key_int;
//						int res = black_list_check(black_list, chek, alph_data_str);
//						key_data.push_back(res);
//						black_list.push_back(res);
//
//					}
//					else {
//						int chek = alph_data_str[i] + key_int;
//						int res = black_list_check(black_list, chek, alph_data_str);
//						key_data.push_back(res);
//						black_list.push_back(res);
//
//
//					}
//				}
//				
//				for (int i = 0; i < alph_data_str.size(); i++) {
//					string aa;
//					string ee;
//					aa.push_back(alph_data_str[i]);
//					ee.push_back(key_data[i]);
//					key.at("key").push_back(json::array({ aa,ee }));
//				}
//				ofstream key_file(path_save_file);
//				key_file << key;
//				key_file.close();
//			}
//			else {
//				cout << "alph is not correct!" << endl;
//			}
//		}
//		else {
//			cout << "ERROR" << endl;
//		}
//	}



//		bool trriger = 0;
//		string path_alph;
//		cout << "Enter the path to the alphabet(.alph): "; cin >> path_alph; cout << endl;
//		if (path_alph.substr(path_alph.find_last_of(".") + 1) != "alph") {
//			trriger = 1;
//		}
//		if (path_save_file.substr(path_save_file.find_last_of(".") + 1) != "key") {
//			trriger = 1;
//		}
//		if (FileIsExist(path_alph)) {
//			trriger = 1;
//		}
//		if (trriger == 0) {
//			ifstream alph_file(path_alph);
//			json alph;
//			alph_file >> alph;
//			alph_file.close();
//			auto array_alph = alph.find("alph");
//			if (array_alph != alph.end()) { 
//				json key = { {"alg_type", "gamming"},{"key",{}} };
//
//				string alph_data_str;
//				json alph_data = alph.at("alph");
//
//				json::iterator it = alph_data.begin();
//				for (int i = 0; i < alph.at("alph").size(); i++) { 
//					string tt = *it;
//					alph_data_str.push_back(tt[0]);
//					it++;
//				}
//				string key_data;
//				string black_list = "";
//				srand(time(0));
//				for (int i = 0; i < alph_data_str.size(); i++) {
//					int key_int = rand() % 10;
//					int minus = key_int % 2;
//					if (minus == 0) {
//						int chek = alph_data_str[i] - key_int;
//						int res = black_list_check(black_list, chek, alph_data_str);
//						key_data.push_back(res);
//						black_list.push_back(res);
//
//					}
//					else {
//						int chek = alph_data_str[i] + key_int;
//						int res = black_list_check(black_list, chek, alph_data_str);
//						key_data.push_back(res);
//						black_list.push_back(res);
//
//
//					}
//				}
//
//				for (int i = 0; i < alph_data_str.size(); i++) {
//					string aa;
//					string ee;
//					aa.push_back(alph_data_str[i]);
//					ee.push_back(key_data[i]);
//					key.at("key").push_back(json::array({ aa,ee }));
//				}
//				
//				ofstream key_file(path_save_file);
//				key_file << key;
//				key_file.close();
//			}
//			else {
//				cout << "alph is not correct!" << endl;
//			}
//		}
//		else {
//			cout << "ERROR" << endl;
//		}
//	}