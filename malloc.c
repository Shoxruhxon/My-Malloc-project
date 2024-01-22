#include "my_malloc.h"
const int SAVE_MAXMEM = 2048;
Encipher_str *arr_encrypt[1024];
void* special_points = NULL;
int size_fuse = 0, arr_indicator = 0;

void give_mem(){
    special_points = mmap(NULL, SAVE_MAXMEM, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
}


void* scaning_free(size_t bulk_sz){
    if(arr_indicator == 0){
        return NULL;
    }
    if(arr_encrypt[arr_indicator] && arr_encrypt[arr_indicator]->absolve == true){
        return NULL;
    }
    else{
        for(int i = 0; i < arr_indicator; i++){
            if(arr_encrypt[i]->length_s == bulk_sz){
                if(arr_encrypt[i]->absolve == false){
                    continue;
                }
                return arr_encrypt[i]->point_ret;
            }
        }
        return NULL;
    }
}

void encrypt_part(size_t amount_arr){
    arr_encrypt[arr_indicator] = (Encipher_str*)special_points;
    arr_encrypt[arr_indicator]->point_ret = sizeof(Encipher_str) + special_points;
    special_points += (sizeof(Encipher_str) + amount_arr);
    arr_encrypt[arr_indicator]->absolve = false;
    arr_encrypt[arr_indicator]->length_s = amount_arr;
    size_fuse += (sizeof(Encipher_str) + amount_arr);
    arr_indicator++;
}

void my_free(void* grab_elem){
    if(grab_elem != NULL){
        for(int j = 0; j < arr_indicator; j++){
            if(arr_encrypt[j]->point_ret == grab_elem){
                if(arr_encrypt[j]->absolve == false){
                    arr_encrypt[j]->absolve = true;
                    fill_wnull(arr_encrypt[j]->point_ret, arr_encrypt[j]->length_s);
                }
                else{
                    perror("double free");
                }
            }
        }
    }
}

void* my_malloc(size_t dimention_arr){
    if(special_points == NULL){
        give_mem();
    }
    void* res_searchingp = scaning_free(dimention_arr);
    if(res_searchingp == NULL){
        encrypt_part(dimention_arr);
    }
    res_searchingp = arr_encrypt[arr_indicator-1]->point_ret;
    return res_searchingp;
}


void* my_calloc(size_t get_bulk, size_t take_sz){
    int overal_ssize = get_bulk + take_sz;
    size_t size_box = overal_ssize;
    void* mem_m_alloc = my_malloc(size_box);
    fill_wnull(mem_m_alloc, size_box);

    return mem_m_alloc;
}

void* my_realloc(void* elem_1, size_t get_ssize){
    size_t save_bulk;
    Encipher_str* hash_part;
    for(int i = 0; i < arr_indicator; i++){
        if(arr_encrypt[i]->point_ret == elem_1){
            hash_part = arr_encrypt[i];
            save_bulk = arr_encrypt[i]->length_s;
       }
    }
    if(hash_part == NULL){
        return my_malloc(get_ssize);
    }
    void* memory = my_malloc(get_ssize);
    memcpy(memory, elem_1, save_bulk);
    my_free(elem_1);
    return memory;
}

int main()
{
    char* test_mem1 = (char*)my_malloc(7*sizeof(char));
    strcpy(test_mem1, "hello ");
    char*sec_mem = my_realloc(test_mem1, 14);
    strcat(sec_mem, "world");
    printf("%s\n", sec_mem);
    
    char*test_mem2 = my_malloc(40*sizeof(char));
    strcpy(test_mem2, "kdvoflbmofbmpmfzdpbkmdfpkb[gmp");
    printf("%s\n", test_mem2);

    char* test_mem3 = (char*)my_calloc(20, sizeof(char));
    strcpy(test_mem3, "have a nice day");
    printf("%s\n", test_mem3);
    my_free(test_mem3);
    
    return 0;
}