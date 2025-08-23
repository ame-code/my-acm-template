#include <bits/stdc++.h>
struct KMP
{
	std::string pattern;
	std::vector<int> border;

    KMP() {};
    KMP(auto&& str) : pattern(std::forward<decltype(str)>(str)) {
        init_border();
    }
    void init(auto&& str) {
        init_pattern(std::forward<decltype(str)>(str));
        init_border();
    }
    void init_border() {
		border.assign(pattern.size(), 0);
		for (int i = 1, j = 0; i < std::ssize(pattern); ++i)
		{
			while (j > 0 && pattern[i] != pattern[j])
			{
				j = border[j - 1];
			}
			if (pattern[i] == pattern[j])j++;
			border[i] = j;
		}
    }
	void init_pattern(auto&& str)
	{
		this->pattern = std::forward<decltype(str)>(str);
	}
	std::vector<int> find(const std::string& text)
	{
		std::vector<int> pos;
		for (int i = 0, j = 0; i < std::ssize(text); ++i)
		{
			while (j > 0 && text[i] != pattern[j])
			{
				j = border[j - 1];
			}
			if (text[i] == pattern[j])j++;
			if (j == std::ssize(pattern))
			{
				pos.push_back(i - j + 1);
				j = border[j - 1];
			}
		}
		return pos;
	}
	auto operator[](int idx) const
	{
		return border[idx];
	}
};