
import re
import sys
import json

with open('url.list.y', 'w') as f_y: 
    with open('url.list.feature', 'w') as f_f: 
        with open('url.list.tag', 'w') as f_t:  
            for i in xrange(0, 100): 
                file_name = "data/1151/1143951076383298983/" +  str(i + 1) + '.html'
                try: 
                    fp = open(file_name)
                    arrJson = json.load(fp)
                    if arrJson is None: 
                        raise Exception(' not json ')

                    if arrJson['msg'] != 'ok': 
                        raise Exception('msg not ok')

                    if len(arrJson['data']) == 0: 
                        raise Exception('data is empty')

                    for item in arrJson['data']: 
                        name = item['name']
                        sid  = item['url'].replace('https://m.anjuke.com/bj/community', '').replace('/', '')

                        url = 'm.anjuke.com/bj/trendency/community/%s/?from=community_jjzs' % sid
                        f_y.write(url + '\n')
                        url = 'm.anjuke.com/bj/community/%s/?from=m_community_list&t_version=15088976601508897654946' % sid
                        f_f.write(url + '\n')
                        url = 'm.anjuke.com/ajax/community/jiedu/tag/?community_id=%s' % sid
                        f_t.write(url + '\n')

                except Exception as e: 
                    print file_name
                    print e
