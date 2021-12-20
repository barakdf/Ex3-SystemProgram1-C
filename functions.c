#include <stdio.h>
#include <string.h>
#include "functions.h"
#include <ctype.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0


//int gValue(char);
int gValue(char c) {
    if (isalpha(c)) {
        int ans = tolower(c);
        return ans - 96;
    }
    return 0;
}


void Gematria(char word[], char text[], char str[]) {
//    int test = gValue('i') + gValue('n') + gValue('.');
//    int test2 = gValue('f') + gValue('i') + gValue('s') + gValue('h');
//    printf("TEST GEM: ==> %d\n", test);
//    printf("TEST GEM: ==> %d\n", test2);

    strcat(str, "Gematria Sequences: ");
//    str = "Gematria Sequences: ";
    int first_seq = TRUE;
    int word_g = 0;
    for (int i = 0; i < strlen(word); ++i) {
        word_g += gValue(word[i]);
    }
    int g_sum = 0;
    int j = 0;
    unsigned long str_index = strlen(str), total_string_len = strlen(text);
    for (int i = 0; j < total_string_len;) {
        if (!isalpha(text[i])) {
            i++;
            continue;
        }
        if (g_sum + gValue(text[j]) < word_g || !isalpha(text[j])) {
            g_sum += gValue(text[j]);
            j++;
        } else if (g_sum + gValue(text[j]) == word_g) {
            g_sum += gValue(text[j]);
            if (!first_seq) {
                str[str_index++] = '~';
            }
            for (int k = i; k <= j; ++k) {
                str[str_index++] = text[k];
                first_seq = FALSE;
            }
            j++;
        } else {
            g_sum -= gValue(text[i]);
            i++;
        }
    }
    str[str_index] = '\0';
    printf("%s\n", str);
//    fflush(stdout);
}

int isEqualString(const char s1[], const char s2[], unsigned long n) {
    int len = (int) n;
//    if(s2[0] == ' ') {
//        return 0;
//    }
    for (int i = 1, j = 1; j < len; ++i, ++j) {
        while (s1[i] != s2[j] && s2[j] == ' ') {
            j++;
            len++;
        }
        if (s1[i] != s2[j]) {
            return 0;
        }

    }
    return len;
}

void reversed(char word1[], char word2[]) {
    unsigned long word_len = strlen(word1);
    for (int i = 0; i < word_len; ++i) {
        word2[i] = word1[word_len - 1 - i];
    }
}

void castAtbash(char word[]) {
    unsigned long len = strlen(word);
    for (int i = 0; i < len; ++i) {
        if (word[i] >= 'a' && word[i] <= 'z') {
            int temp = word[i] - 97;
            word[i] = (char) (122 - temp);
        } else if (word[i] >= 'A' && word[i] <= 'Z') {
            int temp = word[i] - 65;
            word[i] = (char) (90 - temp);
        }
    }
}

void Atbash(char word[], char text[], char str[]) {
    int len_letter = strlen(word), len_text = strlen(text);
    char temp_word[len_letter + 1], temp_text[len_text + 1];
    bool first_seq = true;
    strncpy(temp_word, word, len_letter);
    temp_text[len_text] = temp_word[len_letter] = '\0';
    castAtbash(temp_word);
    strncpy(temp_text, text, len_text);
    char revers[len_letter + 1];
    reversed(temp_word, revers);
    revers[len_letter] = '\0';

//    printf("REVERSE: %s\n", revers);

    strcat(str, "");
    printf("Atbash Sequences:%c", ' ');
    unsigned long str_index = 0;
    if (len_text >= len_letter) {
        for (int i = 0; i <= len_text - len_letter; i++) {
            if (isEqualString(temp_word, temp_text + i, len_letter)) {
                if (!first_seq) {
                    str[str_index++] = '~';
                }
                for (int j = i; j < i + isEqualString(temp_word, temp_text + i, len_letter); ++j) {
                    str[str_index++] = temp_text[j];
                }
                first_seq = false;
            } else if (isEqualString(revers, temp_text + i, len_letter)) {
                if (!first_seq) {
                    str[str_index++] = '~';
                }
                for (int j = i; j < i + isEqualString(revers, temp_text + i, len_letter); ++j) {
                    str[str_index++] = temp_text[j];
                }
                first_seq = false;
            }
        }
    }
    str[str_index] = '\0';
    printf("%s\n", str);
//    fflush(stdout);
}

bool contain(char word[], char container[], char c) {
    unsigned long word_len = strlen(word);
    bool flag = false;
    int shown = 0;
    for (int i = 0; i < word_len; ++i) {
        if (word[i] == c) {
            shown ++;
            flag = true;
        }
    }

    if (flag) {
        unsigned long container_len = strlen(container);
        for (int i = 0; i < container_len; ++i) {
            if (container[i] == c) {
                shown --;
                if(shown == 0) {
                    return false;
                }
            }
        }
    } else {
        return false;
    }
    return true;
}

bool tofes(int i, int j, char text[], char word[]) {
    unsigned long word_len = strlen(word);
    int contain[255];
    for (int k = 0; k <= word_len; ++k) {
        contain[(int)word[k]] = 0;
    }
    for (int k = 0; k < word_len; ++k) {
        contain[(int)word[k]] += 1;
//        printf(", %d", contain[(int)word[k]]);
    }
//    printf("\n");
    for (int k = i; k <= j; ++k) {
        bool flag = false;
        if(text[k] == ' ') {
            continue;
        }
        char temp = text[k];
        for (int l = 0; l < word_len; ++l) {

            if(temp == word[l]) {
//                printf("word %c " , word[l]);
//                printf("temp %c ", temp);
                if(contain[word[l]] > 0) {
//                    printf("true \n");
                    flag = true;
                    contain[word[l]] -= 1;
                    break;
                }
            }
        }
        if(!flag) {
//            printf("------------->\n");
            return false;
        }
    }
//    printf("------------->\n");
    return true;
}

void Anagram(char word[], char text[], char str[]) {
    strcat(str, "");
    printf("Anagram Sequences:%c", ' ');

    bool first_seq = true;
    int str_index = 0;
    unsigned long len = strlen(text), j = strlen(word) - 1;
    int i = 0;
    while (j < len) {
        if(text[i] == ' ') {
            i++;
            if((j-i) < strlen(word) - 1) {
                j++;
            }
        }
        if(text[j] == ' ') {
            j++;
        }
        if(tofes(i, j, text, word)) {
            if(!first_seq) {
                str[str_index++] = '~';
            }
            for (int k = i; k <= j; ++k) {
                str[str_index++] = text[k];
            }
            first_seq = false;
//            str[str_index++] = '\0';
        }
        j++;
        i++;
    }
    str[str_index] = '\0';
    printf("%s", str);
//    fflush(stdout);
}

//
//    strcat(str, "Anagram Sequences: ");
//    int first_seq = TRUE;
//    int j = 0;
//    unsigned long an_index = strlen(str);
//    unsigned long total_string_len = strlen(text);
//    char container[strlen(text)];
//    container[0] = '\0';
//    int con_index = 0, forward = 0;
//    unsigned long num_of_chars = 0, word_len = strlen(word);
//    for (int i = 0; i <= total_string_len;) {
//        if(text[j] == '!') {
//            printf("HEREE %d ", j);
//        }
//        if (text[j] == ' ') {
//            container[con_index] = ' ';
//            con_index++;
//            container[con_index] = '\0';
//            j++;
//            continue;
//        } else if (contain(word, container + forward, text[j])) {
//            container[con_index++] = text[j];
//            container[con_index] = '\0';
//            num_of_chars++;
//            j++;
//        } else {
//            if (!contain(word, container + forward + 1, text[j])) {
//                j++;
//                i = j;
//                forward = i;
//            } else {
//
//
//                while (text[i] == ' ') {
//                    i++;
//                    forward++;
//                }
//                i++;
//                num_of_chars--;
//                forward++;
//
////            num_of_chars = 0;
//            }
//            container[++con_index + forward] = '\0';
//        }
//        if (num_of_chars == word_len) {
//            printf("IN CHAR %d ", i);
//            if (!first_seq) {
//                str[an_index++] = '~';
//            }
//            for (int k = i; k < j; ++k) {
//                if(text[k] == ' ') {
//                    i++;
//                    forward++;
//                    k++;
//                }
//                if(text[k] == ' ') {// check this;
//                    continue;
//                }
//                str[an_index++] = text[k];
////                printf("HERE %c\n", text[k]);
//            }
//            first_seq = FALSE;
//            i++;
//            forward++;
//            num_of_chars -= 1;
//        }
//    }
//    str[an_index] = '\0';
////    printf("LEN__ %lu\n", strlen(str));

