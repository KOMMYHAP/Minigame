#pragma once

namespace BaseUtils
{
	template <typename T, typename Container>
	void Remove(Container & c, shared_ptr<T> ptr)
	{
		if (!ptr)
		{
			return;
		}

		for (auto it = c.begin(); it != c.end(); )
		{
			auto && elem = *it;
			if (elem && std::addressof(*elem) == std::addressof(*ptr))
			{
				it = c.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

}