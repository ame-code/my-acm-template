#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>
#include "../DataStructure/BitTraverser.hpp"
namespace Trie {

template< typename Node >
class Nodes {
	std::vector<Node> nodes_;

protected:
	Nodes(): nodes_(1, Node{}) {}

	void reserve(std::size_t cap) { nodes_.reserve(cap); }

	std::size_t alloc() {
		nodes_.emplace_back(Node{});
		return nodes_.size() - 1;
	}

	Node& node(std::size_t i) {
		return nodes_[i];
	}

	const Node& node(std::size_t i) const {
		return nodes_[i];
	}
};

struct LowerToIndex {
	unsigned char operator()(char c) const {
		return c - 'a';
	}
};

template < std::size_t Size >
struct ASCIINode {
	std::array<std::size_t, Size> next_{};
	std::size_t count_ = 0;
};

struct MaxXorNode {
	std::array<std::size_t, 2> next_{};
	std::size_t count_ = 0;
};

struct AllXorNode {
	std::array<std::size_t, 2> next_{};
	std::size_t count_ = 0;
	std::size_t xor_val_ = 0;
};

template < std::size_t Size = 26, typename Mapping = LowerToIndex >
class ASCII : private Nodes<ASCIINode<Size>>, private Mapping {
	using Base = Nodes<ASCIINode<Size>>;
	using Base::alloc;
	using Base::node;

public:
	ASCII(): Base(), Mapping() {}
	ASCII(const Mapping& map): Base(), Mapping(map) {}

	void insert(std::string_view sv) {
		std::size_t p = 0;
		for (char ch : sv) {
			std::size_t i = (*this)(ch);
			if (!node(p).next_[i]) {
				auto next = alloc();
				node(p).next_[i] = next;
			}
			p = node(p).next_[i];
			node(p).count_++;
		}
	}

	std::size_t search(std::string_view sv) const {
		std::size_t p = 0;
		for (char ch : sv) {
			std::size_t i = (*this)(ch);
			if (!node(p).next_[i]) {
				return 0;
			}
			p = node(p).next_[i];
		}

		return node(p).count_;
	}
};

template < std::integral Int >
class MaxXor : private Nodes<MaxXorNode>{
	using Base = Nodes<MaxXorNode>;	
	using U    = std::make_unsigned_t<Int>;
public:
	MaxXor(): Base() {}

	void insert(Int val) {
		std::size_t p = 0;
		for (auto bit : BitHighTraverser(val)) {
			if (!node(p).next_[bit]) {
				auto next = alloc();
				node(p).next_[bit] = next;
			}
			p = node(p).next_[bit];
			node(p).count_++;
		}
	}

	std::size_t search(Int val) const {
		std::size_t p = 0;
		for (auto bit : BitHighTraverser(val)) {
			if (!node(p).next_[bit]) {
				return 0;
			}
			p = node(p).next_[bit];
		}

		return node(p).count_;
	}

	Int max_xor(Int val) const {
		U res = 0;
		std::size_t p = 0;
		for (auto bit : BitHighTraverser(val)) {
			res <<= 1;
			if (node(p).next_[bit ^ 1]) {
				res |= 1;
				bit ^= 1;
			}
			p = node(p).next_[bit];
		}

		return static_cast<Int>(res);
	}
};

template < std::integral Int >
class AllXor : private Nodes<AllXorNode> {
	using Base = Nodes<AllXorNode>;
	using U    = std::make_unsigned_t<Int>;

	void merge(std::size_t p) {
		node(p).count_ = node(p).xor_val_ = 0;
		if (node(p).next_[0]) {
			node(p).count_ += node(node(p).next_[0]).count_;
			node(p).xor_val_ ^= node(node(p).next_[0]).xor_val_ << 1;
		}
		if (node(p).next_[1]) {
			node(p).count_ += node(node(p).next_[1]).count_;
			node(p).xor_val_ ^= node(node(p).next_[1]).xor_val_ << 1 | (node(node(p).next_[1]).count_ & 1);
		}
	}

	void insert_impl(std::size_t p, Int x, unsigned char depth) {
		if (depth >= sizeof(Int) * 8) {
			node(p).count_++;
			return;
		}
		if (node(p).next_[x & 1] == 0) {
			auto next = alloc();
			node(p).next_[x & 1] = next;
		}
		insert_impl(node(p).next_[x & 1], x >> 1, depth + 1);
		merge(p);
	}

	void erase_impl(std::size_t p, Int x, unsigned char depth) {
		if (depth >= sizeof(Int) * 8) {
			node(p).count_--;
			return;
		}
		erase_impl(node(p).next_[x & 1], x >> 1, depth + 1);
		merge(p);
	}
	
	void add_impl(std::size_t p) {
		std::swap(node(p).next_[0], node(p).next_[1]);
		if (node(p).next_[0]) {
			add_impl(node(p).next_[0]);
		}
		merge(p);
	}

public:
	void insert(Int val) {
		insert_impl(0, val, 0);
	}

	std::size_t search(Int val) const {
		std::size_t p = 0;
		for (auto bit : BitLowTraverser(val)) {
			if (!node(p).next_[bit]) {
				return 0;
			}
			p = node(p).next_[bit];
		}

		return node(p).count_;
	}

	void erase(Int val) {
		if (search(val) == 0) {
			return;
		}
		erase_impl(0, val, 0);
	}

	void add() {
		add_impl(0);
	}

	Int all_xor() const {
		return node(0).xor_val_;
	}
};
}
