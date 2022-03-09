# Tobias Rubel CMSC858D HW1

To compile simply run `make`. The mainfile can then be run which will generate all the data used to make the report. Plotting is a little less clean, but you can see the python file in 
the plotting directory. See hosted code on https://github.com/TobiasRubel/CMSC858D-HW1

# Organization

Each part is implemented in its own directory. hpp and cpp files are provided, but the only difference is that the cpp file has an empty main. There is no command line interface. 

The library meets exactly the API described in the project description. To create a rank support object and compute the rank of some element you can do:

```
    sdsl::bit_vector b(16,0);
    b[0] = 1;
    b[3] = 1;
    b[5] = 1;
    b[6] = 1;
    b[7] = 1;
    b[9] = 1;
    b[12] = 1;
    b[14] = 1;

    rank_support rs = rank_support(&b);
    std::cout << rs.rank1(0) << std::endl;

```

Likewise for select support:

```
    sdsl::bit_vector b(16,0);
    b[0] = 1;
    b[3] = 1;
    b[5] = 1;
    b[6] = 1;
    b[7] = 1;
    b[9] = 1;
    b[12] = 1;
    b[14] = 1;

    rank_support rs = rank_support(&b);

    select_support ss = select_support(&rs);
    std::cout << ss.select1(2) << std::endl;

```


And for the Sparse array:

```
    sparse_array sa(10);

    sa.append("foo",1);
    sa.append("bar",5);
    sa.append("baz",9);
    
    std::string a = "";
    sa.get_at_index(0,a);

```


