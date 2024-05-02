### Development version
QT 5.14.2
### Database table structure
```
          User                                  Manager                              Songgroups     
____________________________          ____________________________          __________________________
|    id    |  varchar(10)  |          |    id    |  varchar(10)  |          |   user   | varchar(10) |
|   user   |  varchar(100) |          |  account |  varchar(100) |          | listname | varchar(10) |
| password |  varchar(100) |          | password |  varchar(100)  |          ——————————————————————————
————————————————————————————          ————————————————————————————

        Songlist                             Listofsong
__________________________         _____________________________
|  user  | varchar(10)   |         |    user    | varchar(10)  |
|  url   | varchar(200)  |         |  listname  | varchar(10)  |
|  name  | varchar(10)   |         |    url     | varchar(200) |
|  img   | varchar(200)  |         |    name    | varchar(10)  |
|  lrc   |    TEXT       |         | singername | varchar(10)  |
——————————————————————————         | albumname  | varchar(10)  |
                                   |    time    |     int      | 
                                   |    img     | varchar(200) |
                                   |    lrc     |    TEXT      |
                                   —————————————————————————————
```

### Database build command
```sql
create database musicplayer;
use musicplayer;
create table user(id varchar(10), user varchar(100), password varchar(100));
create table manager(id varchar(10), account varchar(100), password varchar(100));
create table songgroups(user varchar(10), listname varchar(10));
create table songlist(user varchar(10), url varchar(200), name varchar(10), img varchar(200), lrc TEXT);
create table listofsong (user varchar(10), listname varchar(10), url varchar(200), name varchar(10), singername varchar(10), albumname varchar(10), time int, img varchar(200), lrc text);
```
### Sogou music music information interface
这里十分感谢[far-future](https://github.com/far-future)对这次的推动，没有他也没有这次新的更新。  
返回的body字段大家根据需要可以进行二次开发。
```
https://m.kugou.com/app/i/getSongInfo.php?cmd=playInfo&hash={歌曲hash}&album_id={歌曲album}&_=1497972864535"
hash 与 album_id 通过歌曲列表接口获得
```
### Returned body
```
{
    "128privilege":8,
    "320privilege":10,
    "album_audio_id":627986807,
    "album_category":1,
    "album_img":"http://imge.kugou.com/stdmusic/{size}/20240430/20240430225201258272.jpg",
    "albumid":92815756,
    "area_code":"1",
    "audio_group_id":417079351,
    "audio_id":349387714,
    "author_name":"花京院ぺろ、重音テト",
    "authors":
    [
        {
            "author_id":8978882,
            "author_name":"花京院ぺろ",
            "avatar":"",
            "birthday":"",
            "country":"",
            "identity":1,
            "is_publish":1,
            "language":"",
            "type":1
        },
        {
            "author_id":179670,
            "author_name":"重音テト",
            "avatar":"http://singerimg.kugou.com/uploadpic/softhead/{size}/20160509/20160509090227541072.jpg",
            "birthday":"2008-04-01",
            "country":"日本",
            "identity":9,
            "is_publish":1,
            "language":"日本",
            "type":0
        }
    ],
    "backup_url":
    [
        "https://sharefs.hw.kugou.com/202405021713/c851ca7dffc492be364e02d2cff13ee3/v3/3c14558194418a6d9c96b5cc30bb1c9d/yp/full/a1000_u0_p409_s1169424263.mp3"
    ],
    "bitRate":128,
    "choricSinger":"花京院ぺろ、重音テト",
    "ctype":1009,
    "errcode":0,
    "error":"",
    "extName":"mp3",
    "extra":
    {
        "128bitrate":128,
        "128filesize":2625477,
        "128hash":"3C14558194418A6D9C96B5CC30BB1C9D",
        "128timelength":164048,
        "320filesize":6563280,
        "320hash":"DDD01C5FF5381A400A5F7485D41A0DB7",
        "320timelength":164048,
        "highbitrate":1874,
        "highfilesize":38440361,
        "highhash":"08C9B6B066C229DA3F9CA1FC8474AB8E",
        "hightimelength":164000,
        "sqbitrate":1042,
        "sqfilesize":21374732,
        "sqhash":"66196DE95A87AE7F40185DB134FE43D9",
        "sqtimelength":164000
    },
    "fail_process":0,
    "fileHead":0,
    "fileName":"花京院ぺろ、重音テト - ラナンキュラス (feat. 重音テト)",
    "fileSize":2625477,
    "hash":"3C14558194418A6D9C96B5CC30BB1C9D",
    "highprivilege":10,
    "imgUrl":"",
    "intro":"",
    "mvhash":"",
    "old_cpy":0,
    "pay_type":0,
    "privilege":8,
    "publish_self_flag":0,
    "q":0,
    "req_albumid":"92815756",
    "req_hash":"3C14558194418A6D9C96B5CC30BB1C9D",
    "singerHead":"",
    "singerId":8978882,
    "singerName":"花京院ぺろ",
    "songName":"ラナンキュラス (feat. 重音テト)",
    "sqprivilege":10,
    "status":1,
    "store_type":"audio",
    "stype":11323,
    "time":1714641233,
    "timeLength":164,
    "topic_remark":"",
    "topic_url":"",
    "trans_param":
    {
        "cid":385299592,
        "classmap":{"attr0":100663304},
        "cpy_attr0":0,
        "cpy_grade":5,
        "cpy_level":1,
        "display":0,
        "display_rate":0,
        "ipmap":{"attr0":1048576},
        "language":"日语",
        "musicpack_advance":0,
        "ogg_128_filesize":1959963,
        "ogg_128_hash":"536079B099766F42EE638AFE7F2B2124",
        "ogg_320_filesize":6900379,
        "ogg_320_hash":"722EFA11ACB4171AE900821B4C6F85AB",
        "pay_block_tpl":1,
        "qualitymap":{"attr0":116}
    },
    "url":"https://sharefs.tx.kugou.com/202405021713/9e1d4e23417f2b663ea8a13a2b3177e2/v3/3c14558194418a6d9c96b5cc30bb1c9d/yp/full/a1000_u0_p409_s1169424263.mp3"
}
```
