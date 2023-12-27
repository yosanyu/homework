def set_logo_path(logos):
    for i in range(len(logos)):
        logos[i] = 'logo/' + logos[i] + '.png'
    return logos

class Data:
    def __init__(self):
        pass

    @staticmethod
    def get_CPBL_team():
        teams = ['中信兄弟', '統一7-ELEVEn獅', 'Rakuten Monkeys', '富邦悍將']
        return teams

    @staticmethod
    def get_CPBL_logo():
        logos = ['CTBC_Brothers', 'Uni-President_Lions', 'Rakuten_Monkeys', 'Fubon_Guardians']
        return  set_logo_path(logos)

    @staticmethod
    def get_CPBL_code():
        code = ['E02', 'L01', 'AJL011', 'B04']
        return code

    @staticmethod
    def get_CPBL_batting():
        batting_score = ['NAME', 'TEAM', 'G', 'PA', 'AB', 'RBI', 'R', 'H', '1B', '2B',
                         '3B', 'HR', 'TB', 'SO', 'SB', 'OBP', 'SLG', 'AVG', 'GIDP',
                         'SAC', 'SF', 'BB', 'IBB', 'HBP', 'CS', 'GO', 'AO', 'G/F',
                         'SB%', 'TA', 'SSA']
        return batting_score

    @staticmethod
    def get_CPBL_bfilter():
        b_filter = [0, 2, 3, 4, 5, 6, 7, 8, 9,
                 10, 11, 13, 14, 15, 16, 17,21]
        return b_filter

    @staticmethod
    def get_CPBL_pitching():
        pitching = ['NAME', 'TEAM', 'G', 'GS', 'GR', 'CG', 'SHO', 'NBB', 'W', 'L', 'SV',
             'BS', 'HLD', 'IP', 'WHIP', 'ERA', 'BF', 'NP', 'H', 'HR', 'BB', 'IBB',
             'HBP', 'SO', 'WP', 'BK', 'R', 'ER', 'GO', 'AO', 'G/F']
        return pitching

    @staticmethod
    def get_CPBL_pfilter():
        p_filter = [0, 2, 3, 4, 8, 9, 10,11, 12, 13, 14, 15,
                    16, 17, 18, 19, 20, 23, 24, 26, 27]
        return p_filter

    @staticmethod
    def get_CPBL_garrison():
        garrison = ['NAME', 'TEAM', 'POS', 'G', 'TC', 'PO', 'A', 'E',
                    'DP', 'TP', 'PB', 'CS', 'SB', 'CS%', 'FPCT']
        return garrison

    @staticmethod
    def get_CPBL_gfilter():
        g_filter = [0, 2, 3, 4, 5, 6, 7,8, 9, 10, 11, 12,
                    13, 14]
        return g_filter
