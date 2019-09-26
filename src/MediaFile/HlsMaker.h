﻿/*
 * MIT License
 *
 * Copyright (c) 2016-2019 xiongziliang <771730766@qq.com>
 *
 * This file is part of ZLMediaKit(https://github.com/xiongziliang/ZLMediaKit).
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef HLSMAKER_H
#define HLSMAKER_H

#include <deque>
#include <tuple>
#include "Common/config.h"
#include "Util/TimeTicker.h"
#include "Util/File.h"
#include "Util/util.h"
#include "Util/logger.h"
using namespace toolkit;

namespace mediakit {

class HlsMaker {
public:
    /**
     * @param seg_duration 切片文件长度
     * @param seg_number 切片个数
     */
    HlsMaker(float seg_duration = 5, uint32_t seg_number = 3);
    virtual ~HlsMaker();

    /**
     * 写入ts数据
     * @param data 数据
     * @param len 数据长度
     * @param timestamp 毫秒时间戳
     */
    void inputData(void *data, uint32_t len, uint32_t timestamp);
protected:
    /**
     * 创建ts切片文件回调
     * @param index
     * @return
     */
    virtual string onOpenFile(int index) = 0;

    /**
     * 删除ts切片文件回调
     * @param index
     */
    virtual void onDelFile(int index) = 0;

    /**
     * 写ts切片文件回调
     * @param data
     * @param len
     */
    virtual void onWriteFile(const char *data, int len) = 0;

    /**
     * 写m3u8文件回调
     * @param data
     * @param len
     */
    virtual void onWriteHls(const char *data, int len) = 0;

    /**
     * 生成m3u8文件
     * @param eof true代表点播
     */
    void makeIndexFile(bool eof = false);
    void delOldFile();
    void addNewFile(uint32_t timestamp);
protected:
    uint32_t _seg_number = 0;
private:
    float _seg_duration = 0;
    uint64_t _file_index = 0;
    Ticker _ticker;
    string _last_file_name;
    std::deque<tuple<int,string> > _seg_dur_list;
};

}//namespace mediakit
#endif //HLSMAKER_H
