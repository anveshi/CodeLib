template < typename NODETYPE, typename UPDATETYPE, typename RANGETYPE>
class SegmentTree {

  public:

    SegmentTree( \

      RANGETYPE n, \
      NODETYPE (merge) (NODETYPE, NODETYPE), \
      NODETYPE (leafNodeValue) (RANGETYPE), \
      void (updateNode) (NODETYPE &, UPDATETYPE &, RANGETYPE &, RANGETYPE &) , \
      void (updateLazy) (UPDATETYPE &, UPDATETYPE &), \
      UPDATETYPE defaultLazyValueArg, \
      NODETYPE outOfRangeArg) {

      outOfRange = outOfRangeArg;
      defaultLazyValue = defaultLazyValueArg;
      size = n;
      tree = new NODETYPE[n << 3];
      lazy = new UPDATETYPE[n << 3];
      build(1, 0, size - 1);
    }


    void update(RANGETYPE start, RANGETYPE end, UPDATETYPE value) {
      update(1, 0, size - 1, start, end, value);
    }

    NODETYPE query(RANGETYPE start, RANGETYPE end) {
      return query(1, 0, size - 1, start, end);
    }

  private:

    NODETYPE outOfRange;       // When we query outside require segment, what value to return by default, so that main query has no impact.
    UPDATETYPE defaultLazyValue; // Default value of lazy, initially.. or after updating a node.

    void build(RANGETYPE node, RANGETYPE start, RANGETYPE end) {
      RANGETYPE into2 = node << 1, mid = (start + end) / 2;
      if(start == end) {
        tree[node] = leafNodeValue(start);
        lazy[node] = defaultLazyValue;
      } else {
        build(into2, start, mid), build(into2 + 1, mid + 1, end);
        lazy[node] = defaultLazyValue;
        tree[node] = merge(tree[into2], tree[into2 + 1]);
      }
    }

    void push(RANGETYPE node, RANGETYPE start, RANGETYPE end) {
      if(lazy[node] != defaultLazyValue) {
        updateNode(tree[node], lazy[node], start, end);
        if(start != end) {
          updateLazy(lazy[node + node], lazy[node]);
          updateLazy(lazy[node + node + 1], lazy[node]);
        }
        lazy[node] = defaultLazyValue;
      }
    }

    void update(RANGETYPE node, RANGETYPE start, RANGETYPE end, RANGETYPE rangestart, RANGETYPE rangeend, UPDATETYPE value) {
      RANGETYPE into2 = node << 1, mid = (start + end) / 2;
      push(node, start, end);
      if(start > end || start > rangeend ||  end < rangestart) return;
      if(rangestart <= start && end <= rangeend) {
        updateNode(tree[node], value, start, end);
        if(start != end) {
          updateLazy(lazy[into2 + 1], value);
          updateLazy(lazy[into2], value);
        }
        return;
      }
      update(into2, start, mid, rangestart, rangeend, value), update(into2 + 1, mid + 1, end, rangestart, rangeend, value);
      tree[node] = merge(tree[into2], tree[into2 + 1]);
    }

    NODETYPE query(RANGETYPE node, RANGETYPE start, RANGETYPE end, RANGETYPE rangestart, RANGETYPE rangeend) {
      RANGETYPE into2 = node << 1, mid = (start + end) / 2;
      if(start > end || start > rangeend ||  end < rangestart) return outOfRange;
      push(node, start, end);
      if(rangestart <= start && end <= rangeend) return tree[node];
      return merge( query(into2, start, mid, rangestart, rangeend), query(into2 + 1, mid + 1, end, rangestart, rangeend));
    }

    long long int size;
    NODETYPE * tree;
    UPDATETYPE * lazy;

};