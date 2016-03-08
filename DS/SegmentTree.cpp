class SegmentTree {
  public:

    SegmentTree(int n) {
      size = n;
      tree = new int[n << 3];
      lazy = new int[n << 3];
      build(1, 0, size - 1);
    }

    void update(int start, int end, int value) {
      update(1, 0, size - 1, start, end, value);
    }

    int query(int start, int end) {
      return query(1, 0, size - 1, start, end);
    }

  private:

    int outOfRange = 0;       // When we query outside require segment, what value to return by default, so that main query has no impact.
    int defaultLazyValue = 0; // Default value of lazy, initially.. or after updating a node.

    // How to merge two nodes of two subtrees to form root of main-tree.
    inline int merge(int a, int b) {
      return a + b;
    }

    // Given value of lazy at a node, how to update the value (tree[node]) that node stores.
    inline void updateNodeFromLazy(int & node, int & start, int & end) {
      tree[node] += lazy[node] * (end - start + 1);
    }

    // Propagte lazy down.
    inline void updateChildrenLazy(int & node, int & start, int & end) {
      int into2 = node << 1;
      lazy[into2] += lazy[node];
      lazy[into2 + 1] += lazy[node];
    }

    // Update a node, given update value.
    inline void updateNodeByValue(int & node, int & start, int & end, int & value) {
      tree[node] += value * (end - start + 1);
    }

    // Add current update to lazy of a node's children.
    inline void updateLazyByValue(int & node, int & start, int & end, int & into2, int & value) {
      lazy[into2] += value; lazy[into2 + 1] += value;
    }

    // How to calculate value at leaf node while building the segment-tree.
    inline int leafNodeValue(int start) {
   return 0;
    }


    void build(int node, int start, int end) {
      int into2 = node << 1, mid = (start + end) / 2;
      if(start == end) {
        tree[node] = leafNodeValue(start);
        lazy[node] = defaultLazyValue;
      } else {
        build(into2, start, mid), build(into2 + 1, mid + 1, end);
        lazy[node] = defaultLazyValue;
        tree[node] = merge(tree[into2], tree[into2 + 1]);
      }
    }

    void push(int node, int start, int end) {
      if(lazy[node] != defaultLazyValue) {
        updateNodeFromLazy(node, start, end);
        if(start != end) updateChildrenLazy(node, start, end);
        lazy[node] = defaultLazyValue;
      }
    }

    void update(int node, int start, int end, int rangestart, int rangeend, int value) {
      int into2 = node << 1, mid = (start + end) / 2;
      push(node, start, end);
      if(start > end || start > rangeend ||  end < rangestart) return;
      if(rangestart <= start && end <= rangeend) {
        updateNodeByValue(node, start, end, value);
        if(start != end) updateLazyByValue(node, start, end, into2, value);
        return;
      }
      update(into2, start, mid, rangestart, rangeend, value), update(into2 + 1, mid + 1, end, rangestart, rangeend, value);
      tree[node] = merge(tree[into2], tree[into2 + 1]);
    }

    int query(int node, int start, int end, int rangestart, int rangeend) {
      int into2 = node << 1, mid = (start + end) / 2;
      if(start > end || start > rangeend ||  end < rangestart) return outOfRange;
      push(node, start, end);
      if(rangestart <= start && end <= rangeend) return tree[node];
      return merge( query(into2, start, mid, rangestart, rangeend), query(into2 + 1, mid + 1, end, rangestart, rangeend));
    }

    int size, * tree, * lazy;

};