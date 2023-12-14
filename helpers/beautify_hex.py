def main():
    full_hex_list = [
        '0B55E583B0A5924A82D8DD5280AC7C44',
        '0C3FFFD5C010671A2C7DE6951D2D948D',
        '0DAB7B08D0AD40479407AEF96F5B36E3',
        '0ED434ACE0A929A09F89764DF9C11351',
        '0F40B071F0140EFD27F33E218BB7B13F',
        '1054974EC3813599D1AC0A0F2C6CB22F',
        '11C01393D33C12C469D642635E1A1041',
        '12BF5C37E3387B2362589AD7C88035F3',
        '132BD8EAF3855C7EDA22D2BBBAF6979D',
        '1441C2BC8330A92E7487E97C27777F54',
        '15D54661938D8E73CCFDA1105501DD3A',
        '16AA09C5A389E794C77379A4C39BF888',
        '173E8D18B334C0C97F0931C8B1ED5AE6',
        '187E3D694320CE3458FA0FE93A5AEBD9',
        '19EAB9B4539DE969E0804785482C49B7',
        '1A95F6106399808EEB0E9F31DEB66C05',
        '1B0172CD7324A7D35374D75DACC0CE6B',
        '1C6B689B03915283FDD1EC9A314126A2',
        '1DFFEC46132C75DE45ABA4F6433784CC',
        '1E80A3E223281C394E257C42D5ADA17E',
        '1F14273F33953B64F65F342EA7DB0310',
        '20A8ED9C45C16AF1619B141E58D8A75E',
    ]

    for full_hex in full_hex_list:
        print('{', end='')
        for i in range(0, len(full_hex), 2):
            print(
                f'0x{full_hex[i].lower()}{full_hex[i+1].lower()}', 
                end=(', ' if i + 2 != len(full_hex) else '')
            )
        print('}', end='')
        print()

    # print('{', end='')
    # for i in range(0, len(full_hex), 2):
    #     print(
    #         f'0x{full_hex[i].lower()}{full_hex[i+1].lower()}', 
    #         end=(', ' if i + 2 != len(full_hex) else '')
    #     )
    # print('}', end='')
    

if __name__ == "__main__":
    main()