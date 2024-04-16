#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gtest/gtest.h"
#include "adt_list.h"

namespace
{

    int delfunc_char(void *e)
    {
        free(e);
        return 0;
    }
    void *dupfunc_char(void *e)
    {
        char *ret_val = (char *)malloc(sizeof(char));
        if (ret_val)
        {
            *ret_val = *((char *)e);
        }
        return ret_val;
    }
    char *to_string_char(void *e)
    {
        char *ret_val = (char *)calloc(2, sizeof(char));
        if (ret_val)
        {
            ret_val[0] = *((char *)e);
        }
        return ret_val;
    }

    TEST(list, creation)
    {
        c_double_list_head *lh = dl_create(&dupfunc_char, &delfunc_char, &to_string_char);
        char buf[1024];
        dl_list2str(&lh, &buf[0], sizeof(buf));
        ASSERT_TRUE(lh != NULL) << "List Head shouldn't be NUL but is" << std::endl;
        ASSERT_STREQ(buf, "{ }") << "buff" << buf << " != '{ }'" << std::endl;
        dl_delete(&lh);
    }

    TEST(list, add)
    {
        c_double_list_head *lh = dl_create(&dupfunc_char, &delfunc_char, &to_string_char);
        char buf[1024];
        char list[] = {'H', 'I', 'T', 'H', 'E'};
        dl_list2str(&lh, &buf[0], sizeof(buf));
        ASSERT_TRUE(lh != NULL) << "List Head shouldn't be NUL but is" << std::endl;
        ASSERT_STREQ(buf, "{ }") << "buf" << buf << " != '{ }'" << std::endl;
        for (int x = 0; x < sizeof(list); x++)
        {
            dl_add_element(&lh, (void *)(&list[x]));
            dl_list2str(&lh, buf, sizeof(buf));
        }
        dl_list2str(&lh, &buf[0], sizeof(buf));
        ASSERT_STREQ(buf, "{ H, I, T, H, E, }") << "buf" << buf << " != '{ H, I, T, H, E, }'" << std::endl;
        dl_delete(&lh);
    }

    /* ### P01 (*) Find the last box of a list.
    ** Example:
    ** * (my-last '(a b c d))
    ** (D)
    */
    TEST(c_99, problem_1)
    {
        c_double_list_head *list = dl_create(&dupfunc_char, &delfunc_char, &to_string_char);
        char buf[1024];
        c_double_list_head *result[5];
        char list_data[] = {'a', 'b', 'c', 'd'};
        int x;
        for (x = 0; x < sizeof(list_data); x++)
        {
            result[x] = dl_last(&list);
            dl_list2str(&(result[x]), buf, sizeof(buf));
            // EXPECT_STREQ(buf, "  ") << "buf" << buf << " != '  '" << std::endl;
            dl_add_element(&list, (void *)(&list_data[x]));
        }
        result[x] = dl_last(&list);
        dl_list2str(&(result[x]), buf, sizeof(buf));
        // EXPECT_STREQ(buf, "  ") << "buf2 " << buf << " != '  '" << std::endl;
        ASSERT_STREQ(buf, "{ d, }") << "buf " << buf << " != { d, }" << std::endl;
        for (int i = 0; i < x; i++)
            dl_delete(&(result[i]));
        dl_delete(&list);
    }

}
