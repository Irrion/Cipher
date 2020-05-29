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
		string form = path_key;
		form = form.substr(form.size() - 4);
		if (form == ".key")
		{
			cout << "Enter the path to the alphabet:" << "\t";
			cin >> path_alph;
			cout << endl;
			form = path_alph;
			form = form.substr(form.size() - 5);
			if (form == ".alph")
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
		string form;
		form = path_key;
		form = form.substr(form.size() - 4);
		if (form == ".key")
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
					form = path_cipher;
					form = form.substr(form.size() - 8);
					if (form == ".encrypt")
					{
						cout << "Enter the path to the file with text:" << "\t";
						cin >> path_txt;
						cout << endl;
						form = path_txt;
						form = form.substr(form.size() - 4);
						if (form == ".txt")
						{
							if (fileNOopen(path_txt))
							{
								trig = 1;
							}
							if (trig == 0)
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
		string form;
		form = path_key;
		form = form.substr(form.size() - 4);
		if (form == ".key")
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
					form = path_cipher;
					form = form.substr(form.size() - 8);
					if (form == ".encrypt")
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
							form = path_cipher;
							form = form.substr(form.size() - 4);
							if (form == ".txt")
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
		cout << "Enter the path to the file to save the key:" << "\t";
		cin >> path_key;
		cout << endl;
		string form;
		form = path_key;
		form = form.substr(form.size() - 4);
		if (form == ".key")
		{
			cout << "Enter the path to the file with text:" << "\t";
			cin >> path_txt;
			cout << endl;
			form = path_txt;
			form = form.substr(form.size() - 4);
			if (form == ".txt")
			{
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
				cout << "ERROR. Check the path to the text" << endl;
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
		string form;
		form = path_key;
		form = form.substr(form.size() - 4);
		if (form == ".key")
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
					form = path_cipher;
					form = form.substr(form.size() - 8);
					if (form == ".encrypt")
					{
						cout << "Enter the path to the file with text:" << "\t";
						cin >> path_txt;
						cout << endl;
						form = path_txt;
						form = form.substr(form.size() - 4);
						if (form == ".txt")
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
		string form;
		form = path_key;
		form = form.substr(form.size() - 4);
		if (form == ".key")
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
					form = path_cipher;
					form = form.substr(form.size() - 8);
					
					if (form == ".encrypt")
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
							form = path_deciph;
							form = form.substr(form.size() - 4);
							if (form == ".txt")
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
		srand(time(NULL));
		string path_key;
		string path_alph;
		string path_txt;
		cout << "Enter the path to the file to save the key:" << "\t";
		cin >> path_key;
		cout << endl;
		string form;
		form = path_key;
		form = form.substr(form.size() - 4);
		if (form == ".key")
		{
			cout << "Enter the path to the alphabet:" << "\t";
			cin >> path_alph;
			cout << endl;
			form = path_alph;
			form = form.substr(form.size() - 5);
			if (form == ".alph")
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
						cout << "Enter the path to the file with text:" << "\t";
						cin >> path_txt;
						cout << endl;
						form = path_txt;
						form = form.substr(form.size() - 4);
						if (form == ".txt")
						{
							bool trig = 0;
							if (fileNOopen(path_txt))
							{
								trig = 1;
							}
							if (trig == 0)
							{
								ofstream file_key(path_key);
								ifstream file_txt(path_txt);
								json key = { {"cipher type", "gamming"},{"key",{}} };
								int count = 0;
								int coun = 0;
								int keep;

								while (!file_txt.eof())
								{
									string str;
									string str1;
									string check;
									string word;
									int size = 0;
									file_txt >> str;
									vector<int>key_arr;
									for (int i = 0; i < str.size(); i++)
									{
										for (int j = 0; j < array_alph.size(); j++)
										{
											if (str[i] == array_alph[j])
											{
												size++;
											}
										}
									}
									for (int i = 0; i < size; i++)
									{
										int ran = rand() % 52 + 1;
										key_arr.push_back(ran);
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
							cout << "ERROR. Check the path to the text" << endl;
						}
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
		string path_alph;
		string path_txt;
		string path_cipher;
		cout << "Enter the path to the file with the key:" << "\t";
		cin >> path_key;
		cout << endl;
		string form;
		form = path_key;
		form = form.substr(form.size() - 4);
		if (form == ".key")
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
					cout << "Enter the path to the alphabet:" << "\t";
					cin >> path_alph;
					cout << endl;
					form = path_alph;
					form = form.substr(form.size() - 5);
					if (form == ".alph")
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
								cout << "Enter the path to the file to save the cipher:" << "\t";
								cin >> path_cipher;
								cout << endl;
								form = path_cipher;
								form = form.substr(form.size() - 8);
								if (form == ".encrypt")
								{
									cout << "Enter the path to the file with text:" << "\t";
									cin >> path_txt;
									cout << endl;
									form = path_txt;
									form = form.substr(form.size() - 4);
									if (form == ".txt")
									{
										if (fileNOopen(path_txt))
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

														int idx = 0;
														for (int j = 0; j < str3.size(); j++)
														{
															for (int k = 0; k < array_alph.size(); k++)
															{
																if (str3[j] == array_alph[k])
																{
																	int sum = k + key.at("key").at(i).at(idx);
																	int position = sum % array_alph.size();
																	str3[j] = array_alph[position];
																	idx++;
																	break;
																}
															}
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
		string path_deciph;
		string path_cipher;
		cout << "Enter the path to the file with the key:" << "\t";
		cin >> path_key;
		cout << endl;
		string form;
		form = path_key;
		form = form.substr(form.size() - 4);
		if (form == ".key")
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
					cout << "Enter the path to the alphabet:" << "\t";
					cin >> path_alph;
					cout << endl;
					form = path_alph;
					form = form.substr(form.size() - 5);
					if (form == ".alph")
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
								cout << "Enter the path to the file to save the text:" << "\t";
								cin >> path_deciph;
								cout << endl;
								form = path_deciph;
								form = form.substr(form.size() - 4);
								if (form == ".txt")
								{
									cout << "Enter the path to the file with cipher:" << "\t";
									cin >> path_cipher;
									cout << endl;
									form = path_cipher;
									form = form.substr(form.size() - 8);
									if (form == ".encrypt")
									{
										if (fileNOopen(path_cipher))
										{
											trig = 1;
										}
										if (trig == 0)
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

														int idx = 0;
														for (int j = 0; j < str3.size(); j++)
														{
															for (int k = 0; k < array_alph.size(); k++)
															{
																if (str3[j] == array_alph[k])
																{
																	int sum = k - key.at("key").at(i).at(idx) + array_alph.size();
																	int position = sum % array_alph.size();
																	str3[j] = array_alph[position];
																	idx++;
																	break;
																}
															}
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

											file_ciph.close();
											file_deciph.close();
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
									cout << "ERROR. Check the path to the decipher" << endl;
								}
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