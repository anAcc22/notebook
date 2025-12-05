#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;

// Modular Arithmetic Tools needed for operations in Z/pZ
ll fpw(ll base, ll pw, ll md) {
    base %= md;
    if(pw == 0ll) return 1ll;
    ll bsqr = fpw((base * base) % md, pw >> 1ll, md);

    return (pw & 0b1ll ? (bsqr * base) % md : bsqr);
}

ll minv(ll n, ll md) {
    return fpw(n, md - 2ll, md);
}

ll frac(ll num, ll den, ll md) {
    return (num * minv(den, md)) % md;
}

// Prints a matrix
void matprint(const vvll& m) {
    ll r = m.size();

    if(r == 0ll) {
        cerr << "empty list!" << endl;
        return;
    }

    ll c = m[0ll].size();

    for(ll i = 0ll; i < r; i++) {
        for(ll j = 0ll; j < c; j++) cerr << m[i][j] << " ";
        cerr << "\n";
    }

    cerr << flush;
}

// Multiplies two matrices M1 and M2
// order of operands follows linear algebra conventions :))
vvll matmul(const vvll& m1, const vvll& m2) {
    ll nr = m1.size(), nc = m2[0].size();
    ll maxk = m1.size(); // should be equal to m1[0].size()
    
    vvll res(nr, vll(nc, 0ll));

    for(ll r = 0; r < nr; r++) {
        for(ll k = 0; k < maxk; k++) {
            for(ll c = 0; c < nc; c++) {
                res[r][c] += m1[r][k] * m2[k][c];
            }
        }
    }

    return res;
}

// Matrix multiplication mod p
vvll matmulmod(const vvll& m1, const vvll& m2, ll MOD) {
    ll nr = m1.size(), nc = m2[0].size();
    ll maxk = m1.size(); // should be equal to m1[0].size()
    
    vvll res(nr, vll(nc, 0ll));


    for(ll r = 0; r < nr; r++) {
        for(ll k = 0; k < maxk; k++) {
            for(ll c = 0; c < nc; c++) {
                res[r][c] = (res[r][c] + (m1[r][k] * m2[k][c]) % MOD) % MOD;
            }
        }
    }

    return res;
}

// Matrix-vector multiplication, no modulo
vll matvec(const vvll& m, const vll& v) {
    vll res;
    ll res_size = m.size();
    ll inp_size = v.size();

    for(ll i = 0; i < res_size; i++) {
        ll cur_sum = 0ll;
        for(ll j = 0; j < inp_size; j++) {
            cur_sum += v[j] * m[i][j];
        }
        res.push_back(cur_sum);
    }

    return res;
}

// Matrix-vector multiplication, with modulo
vll matvecmod(const vvll& m, const vll& v, ll MOD) {
    vll res;
    ll res_size = m.size();
    ll inp_size = v.size();

    for(ll i = 0; i < res_size; i++) {
        ll cur_sum = 0ll;
        for(ll j = 0; j < inp_size; j++) {
            cur_sum = (cur_sum + (v[j] * m[i][j]) % MOD) % MOD;
        }
        res.push_back(cur_sum);
    }

    return res;
}

// Creates an identity matrix of size n x n
vvll id_mat(ll n) {
    vvll res;
    for(ll i = 0; i < n; i++) {
        vll res_row(n, 0ll);
        res.push_back(res_row);
    }
    for(ll i = 0; i < n; i++) {
        res[i][i] = 1ll;
    }
    return res;
}

// Fast matrix exponentiation
// m has to be a square matrix
// O(n^3 log pw)
vvll matpowmod(const vvll& m, ll pw, ll md) {
    if(pw == 0) {
        return id_mat(m.size());
    }
    vvll sqr_sqrt = matpowmod(matmulmod(m, m, md), pw >> 1, md);
    return (pw & 1 ? matmulmod(sqr_sqrt, m, md) : sqr_sqrt);
}

// Matrix Addition
vvll matadd(const vvll& m1, const vvll& m2, ll md) {
    ll r1 = m1.size(), c1 = m1[0ll].size();
    ll r2 = m2.size(), c2 = m2[0ll].size();

    assert(r1 == r2 && c1 == c2);

    vvll res(r1, vll(c1, 0ll));

    for(ll i = 0ll; i < r1; i++) for(ll j = 0ll; j < c1; j++) res[i][j] = (m1[i][j] + m2[i][j]) % md;

    return res;
}

// Matrix Subtraction
vvll matsub(const vvll& m1, const vvll& m2, ll md) {
    ll r1 = m1.size(), c1 = m1[0ll].size();
    ll r2 = m2.size(), c2 = m2[0ll].size();

    assert(r1 == r2 && c1 == c2);

    vvll res(r1, vll(c1, 0ll));

    for(ll i = 0ll; i < r1; i++) for(ll j = 0ll; j < c1; j++) res[i][j] = ((m1[i][j] - m2[i][j]) % md + md) % md;

    return res;
}

// Copy a matrix
vvll matcopy(const vvll& mat) {
    ll r = mat.size(), c = mat[0ll].size();

    vvll res(r, vll(c, 0ll));

    for(ll i = 0ll; i < r; i++) for(ll j = 0ll; j < c; j++) res[i][j] = mat[i][j];

    return res;
}

// Matrix Transpose
vvll transpose(const vvll& mat) {
    ll r = mat.size();

    vvll empty;
    if(r == 0ll) return empty;

    ll c = mat[0ll].size();

    if(c == 0ll) return empty;

    vvll res(c, vll(r, 0ll));
    for(ll i = 0ll; i < r; i++) for(ll j = 0ll; j < c; j++) res[j][i] = mat[i][j];

    return res;
}

// In-place Gauss-Jordan Elimination mod p
// lc is the number of columns to reduce. useful for reducing augmented matrices
// returns the determinant
ll gj_inplace(vvll& mat, ll lc, ll md) {
    ll r = mat.size();

    if(r == 0ll) return 0ll;
    ll c = mat[0ll].size();
    if(c == 0ll) return 0ll;

    ll det = 1ll;

    // reducing to row-echelon form
    ll cc = 0ll;
    for(ll cr = 0ll; cr < r && cc < min(c, lc); cr++) {
        // find the first row in [i, r] that's nonzero
        ll fstnonzero = -1ll;

        do {
            for(ll j = cr; j < r; j++) if(mat[j][cc] != 0ll) {fstnonzero = j; break;}

            if(fstnonzero == -1ll) {
                cc ++;
                det = 0ll;
            }
        } while(fstnonzero == -1ll && cc < c);

        if(cc >= c) break;

        if(cr != fstnonzero) {
            swap(mat[cr], mat[fstnonzero]);
            det = (md - det);
        }

        // normalize the current row
        const ll lead_inv = minv(mat[cr][cc], md);

        det = (det * mat[cr][cc]) % md;
        for(ll j = cc; j < c; j++) {
            mat[cr][j] = (mat[cr][j] * lead_inv) % md;

            mat[cr][j] %= md;
            mat[cr][j] += md;
            mat[cr][j] %= md;
        }

        // kill all terms below and above

        for(ll j = 0ll; j < r; j++) {
            if(j == cr) continue;
            ll cur_lead_entry = mat[j][cc];
            if(cur_lead_entry == 0ll) continue;

            ll multi = (cur_lead_entry) % md;

            for(ll i = cc; i < c; i++) {
                mat[j][i] -= (mat[cr][i] * multi) % md;
                mat[j][i] %= md;
                mat[j][i] += md;
                mat[j][i] %= md;
            }
        }

        cc++;
    }

    return det;
}

// Gauss-Jordan Elimination mod p
vvll gj(const vvll& mat, ll lc, ll md) {
    vvll res = matcopy(mat);

    gj_inplace(res, lc, md);

    return res;
}

// Determinant Computation (Using Gauss-Jordan Elimination)
ll determinant(const vvll& mat, ll md) {
    vvll matcpy = matcopy(mat);

    return gj_inplace(matcpy, matcpy[0ll].size(), md);
}

// Row Space Basis Finder (i.e., nonzero row selector)
vvll rowspace(const vvll& mat, ll md) {
    vvll matcpy = matcopy(mat);
    
    ll r = matcpy.size(), c = matcpy[0ll].size();
    gj_inplace(matcpy, c, md);

    vvll res;


    for(ll i = 0ll; i < r; i++) {
        bool all_zero = true;

        for(ll j = 0ll; j < c; j++) if(matcpy[i][j] != 0ll) {all_zero = false; break;}

        if(!all_zero) res.push_back(matcpy[i]);
    }

    return res;
}

// Matrix Rank Finder (Note: rank(A) = dim(Row(A)) = dim(Col(A)))
ll matrank(const vvll& mat, ll md) {
    if((ll)(mat.size()) == 0ll) return 0ll;
    if((ll)(mat[0ll].size()) == 0ll) return 0ll;
    vvll matcpy = matcopy(mat);
    
    ll r = matcpy.size(), c = matcpy[0ll].size();
    gj_inplace(matcpy, c, md);

    ll res = 0ll;


    for(ll i = 0ll; i < r; i++) {
        bool all_zero = true;

        for(ll j = 0ll; j < c; j++) if(matcpy[i][j] != 0ll) {all_zero = false; break;}

        if(!all_zero) res++;
    }

    return res;
}

// Col Space Basis Finder (i.e., leading entry column selector)
// Note: Returns the column space as row vectors!
vvll colspace(const vvll& mat, ll md) {
    vvll matcpy = matcopy(mat);
    
    ll r = matcpy.size(), c = matcpy[0ll].size();


    // reducing to row-echelon form
    vvll res;

    ll cc = 0ll;
    for(ll cr = 0ll; cr < r && cc < c; cr++) {
        // find the first row in [i, r] that's nonzero
        ll fstnonzero = -1ll;

        do {
            for(ll j = cr; j < r; j++) if(matcpy[j][cc] != 0ll) {fstnonzero = j; break;}

            if(fstnonzero == -1ll) {
                cc ++;
            }
        } while(fstnonzero == -1ll && cc < c);

        if(cc >= c) break;

        if(cr != fstnonzero) {
            swap(matcpy[cr], matcpy[fstnonzero]);
        }

        // normalize the current row
        const ll lead_inv = minv(matcpy[cr][cc], md);

        for(ll j = cc; j < c; j++) {
            matcpy[cr][j] = (matcpy[cr][j] * lead_inv) % md;

            matcpy[cr][j] %= md;
            matcpy[cr][j] += md;
            matcpy[cr][j] %= md;
        }

        // kill all terms below and above

        for(ll j = 0ll; j < r; j++) {
            if(j == cr) continue;
            ll cur_lead_entry = matcpy[j][cc];
            if(cur_lead_entry == 0ll) continue;

            ll multi = (cur_lead_entry) % md;

            for(ll i = cc; i < c; i++) {
                matcpy[j][i] -= (matcpy[cr][i] * multi) % md;
                matcpy[j][i] %= md;
                matcpy[j][i] += md;
                matcpy[j][i] %= md;
            }
        }
        
        // Adding the current column with a leading entry to the column basis
        vll next_vec(r, 0ll);

        for(ll i = 0ll; i < r; i++) next_vec[i] = mat[i][cc];

        res.push_back(next_vec);

        cc++;
    }

    return res;
}

// Null Space Basis Finder
vvll nullspace(const vvll& mat, ll md) {
    vvll matcpy = matcopy(mat);
    gj_inplace(matcpy, matcpy[0ll].size(), md);

    // Find the indices of the free parameters
    ll r = matcpy.size(), c = matcpy[0ll].size();
    vll leads;
    vll freeparams;
    set<ll> freeparamsset;

    ll cur_xpos = 0ll;
    for(ll i = 0ll; i < r; i++) {
        while(cur_xpos < c && matcpy[i][cur_xpos] == 0ll) {
            cur_xpos ++;
        }

        if(cur_xpos == c) break;

        leads.push_back(cur_xpos);
    }

    ll cur_ind = 0ll;

    ll num_leads = leads.size();

    for(ll i = 0ll; i < c; i++) {
        if(cur_ind < num_leads && i == leads[cur_ind]) {
            cur_ind++;
        } else {
            freeparams.push_back(i);
            freeparamsset.insert(i);
        }
    }

    // For each free parameter, put a default value into the corresponding vector
    ll num_free_params = freeparams.size();

    if(num_free_params == 0ll) {
        vvll empty;
        return empty;
    }

    vvll res(num_free_params, vll(c, 0ll));

    for(ll i = 0ll; i < num_free_params; i++) {
        res[i][freeparams[i]] = 1ll;
    }

    // Process each leading entry
    cur_xpos = 0ll;
    for(ll i = 0ll; i < r; i++) {
        while(cur_xpos < c && matcpy[i][cur_xpos] == 0ll) {
            cur_xpos ++;
        }

        if(cur_xpos == c) break;

        ll cur_free_param_ind = 0ll;
        for(ll j = 0ll; j < c && cur_free_param_ind < num_free_params; j++) {
            if((ll)(freeparamsset.count(j)) > 0ll) {
                if(j > cur_xpos) {
                    res[cur_free_param_ind][cur_xpos] = (md-matcpy[i][j]) % md;
                }

                cur_free_param_ind++;
            }
        }
    }

    return res;
}

// Matrix Inverter
vvll matinv(const vvll& mat, ll md) {
    ll r = mat.size(), c = mat[0ll].size();
    vvll augmented(r, vll(c << 1ll, 0ll));

    for(ll i = 0ll; i < r; i++) for(ll j = 0ll; j < c; j++) augmented[i][j] = mat[i][j];

    for(ll i = 0ll; i < r; i++) augmented[i][i + c] = 1ll;

    gj_inplace(augmented, c, md);

    vvll res(r, vll(c, 0ll));

    for(ll i = 0ll; i < r; i++) for(ll j = 0ll; j < c; j++) res[i][j] = augmented[i][j + c];

    return res;
}

// Eigenvector Finder given Eigenvalue
// (Could be used to find the stationary distribution of a markov chain)
vvll find_eigenvectors(const vvll& mat, ll lambda, ll md) {
    vvll matcpy = matcopy(mat);

    ll r = matcpy.size();
    assert(r > 0ll);
    ll c = matcpy[0ll].size();
    assert(c > 0ll);

    for(ll i = 0ll; i < r; i++) {
        matcpy[i][i] -= lambda;
        matcpy[i][i] %= md;
        matcpy[i][i] += md;
        matcpy[i][i] %= md;
    }

    vvll eigenvecs = nullspace(matcpy, md);

    return eigenvecs;
}

// Find stationary distribution of a markov chain
vvll find_stationary_distrib(const vvll& tr_mat, ll md) {
    vvll vecs = find_eigenvectors(transpose(tr_mat), 1ll, md);

    ll numvecs = vecs.size();

    if(numvecs == 0ll) {
        vvll empty;
        return empty;
    }

    ll vecdim = vecs[0ll].size();

    for(ll i = 0ll; i < numvecs; i++) {
        ll sum_entries = 0ll;

        for(ll j = 0ll; j < vecdim; j++) {
            sum_entries += vecs[i][j];
            sum_entries %= md;
            sum_entries += md;
            sum_entries %= md;
        }

        for(ll j = 0ll; j < vecdim; j++) {
            vecs[i][j] *= minv(sum_entries, md);
            vecs[i][j] %= md;
            vecs[i][j] += md;
            vecs[i][j] %= md;
        }
    }

    return vecs;
}

// Check basis b1 is subset of b2
bool is_basis_subset(const vvll& b1, const vvll& b2, ll md) {
    ll lc = b2.size();
    ll b1s = b1.size();

    vvll concat = b2;
    for(ll i = 0ll; i < b1s; i++) concat.push_back(b1[i]);

    vvll reducedmat = gj(transpose(concat), lc, md);

    ll nr = reducedmat.size();

    for(ll i = 0ll; i < nr; i++) {
        bool all_left_zeros = true;
        bool all_right_zeros = true;

        for(ll j = 0ll; j < lc; j++) {
            if(reducedmat[i][j] != 0ll) {
                all_left_zeros = false;
                break;
            }
        }

        for(ll j = lc; j < lc + b1s; j++) {
            if(reducedmat[i][j] != 0ll) {
                all_right_zeros = false;
                break;
            }
        }

        // if left does not imply right, return false (formal negation of implication)
        if(all_left_zeros && !all_right_zeros) return false;
    }

    return true;
}

// Check if Two Bases are Equal
bool is_basis_eq(const vvll& b1, const vvll& b2, ll md) {
    return is_basis_subset(b1, b2, md) && is_basis_subset(b2, b1, md);
}

// Check if Vector in Span (equivalent to checking if the span of the singular vector is a subset of the set of vectors)
bool is_in_span(const vll& v, const vvll& b, ll md) {
    vvll b1;
    b1.push_back(v);

    return is_basis_subset(b1, b, md);
}