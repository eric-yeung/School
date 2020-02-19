import java.io.*;


class A2 {
	private final int YY_BUFFER_SIZE = 512;
	private final int YY_F = -1;
	private final int YY_NO_STATE = -1;
	private final int YY_NOT_ACCEPT = 0;
	private final int YY_START = 1;
	private final int YY_END = 2;
	private final int YY_NO_ANCHOR = 4;
	private final int YY_BOL = 128;
	private final int YY_EOF = 129;

  static int[] counters = {0,0,0,0,0}; //counter for each output
  public static void main(String[] args) throws IOException {
    A2 lexer = new A2(new FileReader(new File("A2.input")));
    while (lexer.yylex() != null);
    FileWriter writer = new FileWriter("A2.output");
    writer.write(String.format("identifiers: %d\nkeywords: %d\nnumbers: %d\ncomments: %d\nquotedString: %d", counters[0], counters[1], counters[2], counters[3], counters[4]));
    writer.close();
  }
	private java.io.BufferedReader yy_reader;
	private int yy_buffer_index;
	private int yy_buffer_read;
	private int yy_buffer_start;
	private int yy_buffer_end;
	private char yy_buffer[];
	private boolean yy_at_bol;
	private int yy_lexical_state;

	A2 (java.io.Reader reader) {
		this ();
		if (null == reader) {
			throw (new Error("Error: Bad input stream initializer."));
		}
		yy_reader = new java.io.BufferedReader(reader);
	}

	A2 (java.io.InputStream instream) {
		this ();
		if (null == instream) {
			throw (new Error("Error: Bad input stream initializer."));
		}
		yy_reader = new java.io.BufferedReader(new java.io.InputStreamReader(instream));
	}

	private A2 () {
		yy_buffer = new char[YY_BUFFER_SIZE];
		yy_buffer_read = 0;
		yy_buffer_index = 0;
		yy_buffer_start = 0;
		yy_buffer_end = 0;
		yy_at_bol = true;
		yy_lexical_state = YYINITIAL;
	}

	private boolean yy_eof_done = false;
	private final int YYINITIAL = 0;
	private final int COMMENT = 1;
	private final int yy_state_dtrans[] = {
		0,
		19
	};
	private void yybegin (int state) {
		yy_lexical_state = state;
	}
	private int yy_advance ()
		throws java.io.IOException {
		int next_read;
		int i;
		int j;

		if (yy_buffer_index < yy_buffer_read) {
			return yy_buffer[yy_buffer_index++];
		}

		if (0 != yy_buffer_start) {
			i = yy_buffer_start;
			j = 0;
			while (i < yy_buffer_read) {
				yy_buffer[j] = yy_buffer[i];
				++i;
				++j;
			}
			yy_buffer_end = yy_buffer_end - yy_buffer_start;
			yy_buffer_start = 0;
			yy_buffer_read = j;
			yy_buffer_index = j;
			next_read = yy_reader.read(yy_buffer,
					yy_buffer_read,
					yy_buffer.length - yy_buffer_read);
			if (-1 == next_read) {
				return YY_EOF;
			}
			yy_buffer_read = yy_buffer_read + next_read;
		}

		while (yy_buffer_index >= yy_buffer_read) {
			if (yy_buffer_index >= yy_buffer.length) {
				yy_buffer = yy_double(yy_buffer);
			}
			next_read = yy_reader.read(yy_buffer,
					yy_buffer_read,
					yy_buffer.length - yy_buffer_read);
			if (-1 == next_read) {
				return YY_EOF;
			}
			yy_buffer_read = yy_buffer_read + next_read;
		}
		return yy_buffer[yy_buffer_index++];
	}
	private void yy_move_end () {
		if (yy_buffer_end > yy_buffer_start &&
		    '\n' == yy_buffer[yy_buffer_end-1])
			yy_buffer_end--;
		if (yy_buffer_end > yy_buffer_start &&
		    '\r' == yy_buffer[yy_buffer_end-1])
			yy_buffer_end--;
	}
	private boolean yy_last_was_cr=false;
	private void yy_mark_start () {
		yy_buffer_start = yy_buffer_index;
	}
	private void yy_mark_end () {
		yy_buffer_end = yy_buffer_index;
	}
	private void yy_to_mark () {
		yy_buffer_index = yy_buffer_end;
		yy_at_bol = (yy_buffer_end > yy_buffer_start) &&
		            ('\r' == yy_buffer[yy_buffer_end-1] ||
		             '\n' == yy_buffer[yy_buffer_end-1] ||
		             2028/*LS*/ == yy_buffer[yy_buffer_end-1] ||
		             2029/*PS*/ == yy_buffer[yy_buffer_end-1]);
	}
	private java.lang.String yytext () {
		return (new java.lang.String(yy_buffer,
			yy_buffer_start,
			yy_buffer_end - yy_buffer_start));
	}
	private int yylength () {
		return yy_buffer_end - yy_buffer_start;
	}
	private char[] yy_double (char buf[]) {
		int i;
		char newbuf[];
		newbuf = new char[2*buf.length];
		for (i = 0; i < buf.length; ++i) {
			newbuf[i] = buf[i];
		}
		return newbuf;
	}
	private final int YY_E_INTERNAL = 0;
	private final int YY_E_MATCH = 1;
	private java.lang.String yy_error_string[] = {
		"Error: Internal error.\n",
		"Error: Unmatched input.\n"
	};
	private void yy_error (int code,boolean fatal) {
		java.lang.System.out.print(yy_error_string[code]);
		java.lang.System.out.flush();
		if (fatal) {
			throw new Error("Fatal Error.\n");
		}
	}
	private int[][] unpackFromString(int size1, int size2, String st) {
		int colonIndex = -1;
		String lengthString;
		int sequenceLength = 0;
		int sequenceInteger = 0;

		int commaIndex;
		String workString;

		int res[][] = new int[size1][size2];
		for (int i= 0; i < size1; i++) {
			for (int j= 0; j < size2; j++) {
				if (sequenceLength != 0) {
					res[i][j] = sequenceInteger;
					sequenceLength--;
					continue;
				}
				commaIndex = st.indexOf(',');
				workString = (commaIndex==-1) ? st :
					st.substring(0, commaIndex);
				st = st.substring(commaIndex+1);
				colonIndex = workString.indexOf(':');
				if (colonIndex == -1) {
					res[i][j]=Integer.parseInt(workString);
					continue;
				}
				lengthString =
					workString.substring(colonIndex+1);
				sequenceLength=Integer.parseInt(lengthString);
				workString=workString.substring(0,colonIndex);
				sequenceInteger=Integer.parseInt(workString);
				res[i][j] = sequenceInteger;
				sequenceLength--;
			}
		}
		return res;
	}
	private int yy_acpt[] = {
		/* 0 */ YY_NOT_ACCEPT,
		/* 1 */ YY_NO_ANCHOR,
		/* 2 */ YY_NO_ANCHOR,
		/* 3 */ YY_NO_ANCHOR,
		/* 4 */ YY_NO_ANCHOR,
		/* 5 */ YY_NO_ANCHOR,
		/* 6 */ YY_NO_ANCHOR,
		/* 7 */ YY_NO_ANCHOR,
		/* 8 */ YY_NO_ANCHOR,
		/* 9 */ YY_NOT_ACCEPT,
		/* 10 */ YY_NO_ANCHOR,
		/* 11 */ YY_NO_ANCHOR,
		/* 12 */ YY_NO_ANCHOR,
		/* 13 */ YY_NOT_ACCEPT,
		/* 14 */ YY_NO_ANCHOR,
		/* 15 */ YY_NO_ANCHOR,
		/* 16 */ YY_NOT_ACCEPT,
		/* 17 */ YY_NO_ANCHOR,
		/* 18 */ YY_NO_ANCHOR,
		/* 19 */ YY_NOT_ACCEPT,
		/* 20 */ YY_NO_ANCHOR,
		/* 21 */ YY_NOT_ACCEPT,
		/* 22 */ YY_NO_ANCHOR,
		/* 23 */ YY_NO_ANCHOR,
		/* 24 */ YY_NO_ANCHOR,
		/* 25 */ YY_NO_ANCHOR,
		/* 26 */ YY_NO_ANCHOR,
		/* 27 */ YY_NO_ANCHOR,
		/* 28 */ YY_NO_ANCHOR,
		/* 29 */ YY_NO_ANCHOR,
		/* 30 */ YY_NO_ANCHOR,
		/* 31 */ YY_NO_ANCHOR,
		/* 32 */ YY_NO_ANCHOR,
		/* 33 */ YY_NO_ANCHOR,
		/* 34 */ YY_NO_ANCHOR,
		/* 35 */ YY_NO_ANCHOR,
		/* 36 */ YY_NO_ANCHOR,
		/* 37 */ YY_NO_ANCHOR,
		/* 38 */ YY_NO_ANCHOR,
		/* 39 */ YY_NO_ANCHOR,
		/* 40 */ YY_NO_ANCHOR,
		/* 41 */ YY_NO_ANCHOR,
		/* 42 */ YY_NO_ANCHOR
	};
	private int yy_cmap[] = unpackFromString(1,130,
"4:34,3,4:7,2,4:3,22,1,21:10,4:7,10,17,20,11,9,12,18,20,7,20:2,13,19,16,20:3" +
",6,14,8,15,20,5,20:3,4:6,20:26,4:5,0:2")[0];

	private int yy_rmap[] = unpackFromString(1,43,
"0,1,2,3,4,1,5,1:2,6,1,7,8,9:2,10,8:2,11,12,13,14,15,16,17,18,19,20,21,22,23" +
",24,25,26,27,28,29,30,31,32,5,33,34")[0];

	private int yy_nxt[][] = unpackFromString(35,23,
"1,2,10,14,10,3,33,11,40,26,40:4,41,40:2,42,40,34,40,4,17,-1:25,9,-1:25,40,3" +
"5,40:15,-1:22,4,16,-1:5,40:17,-1:3,7,-1:25,40:7,6,40:3,15,40:5,-1:22,12,-1:" +
"2,13:2,5,13:19,-1:5,40:3,6,40:13,-1:6,40:6,6,40:10,-1,1,10,25,10:20,-1:5,40" +
":6,6,40,6,40:8,-1:2,8,-1:26,40:4,6,40:12,-1:6,40:11,6,40:5,-1:6,40:13,6,40:" +
"3,-1:3,21,-1:25,40:8,28,40:2,18,40:5,-1:6,40:3,38,40,20,40:11,-1:6,40:9,22," +
"40:7,-1:6,40:2,23,40:14,-1:6,40:3,22,40:13,-1:6,40,23,40:15,-1:6,40:11,24,4" +
"0:5,-1:6,40:4,27,40:12,-1:6,40:5,29,40:11,-1:6,40:2,30,40:14,-1:6,40,39,40:" +
"15,-1:6,40:13,29,40:3,-1:6,40:10,31,40:6,-1:6,40:2,32,40:14,-1:6,40:3,36,40" +
":13,-1:6,40:4,37,40:12,-1");

	public String yylex ()
		throws java.io.IOException {
		int yy_lookahead;
		int yy_anchor = YY_NO_ANCHOR;
		int yy_state = yy_state_dtrans[yy_lexical_state];
		int yy_next_state = YY_NO_STATE;
		int yy_last_accept_state = YY_NO_STATE;
		boolean yy_initial = true;
		int yy_this_accept;

		yy_mark_start();
		yy_this_accept = yy_acpt[yy_state];
		if (YY_NOT_ACCEPT != yy_this_accept) {
			yy_last_accept_state = yy_state;
			yy_mark_end();
		}
		while (true) {
			if (yy_initial && yy_at_bol) yy_lookahead = YY_BOL;
			else yy_lookahead = yy_advance();
			yy_next_state = YY_F;
			yy_next_state = yy_nxt[yy_rmap[yy_state]][yy_cmap[yy_lookahead]];
			if (YY_EOF == yy_lookahead && true == yy_initial) {
				return null;
			}
			if (YY_F != yy_next_state) {
				yy_state = yy_next_state;
				yy_initial = false;
				yy_this_accept = yy_acpt[yy_state];
				if (YY_NOT_ACCEPT != yy_this_accept) {
					yy_last_accept_state = yy_state;
					yy_mark_end();
				}
			}
			else {
				if (YY_NO_STATE == yy_last_accept_state) {
					throw (new Error("Lexical Error: Unmatched Input."));
				}
				else {
					yy_anchor = yy_acpt[yy_last_accept_state];
					if (0 != (YY_END & yy_anchor)) {
						yy_move_end();
					}
					yy_to_mark();
					switch (yy_last_accept_state) {
					case 1:
						
					case -2:
						break;
					case 2:
						{}
					case -3:
						break;
					case 3:
						{counters[0]++;}
					case -4:
						break;
					case 4:
						{counters[2]++;}
					case -5:
						break;
					case 5:
						{counters[4]++;}
					case -6:
						break;
					case 6:
						{counters[1]++;}
					case -7:
						break;
					case 7:
						{counters[3]++; yybegin(COMMENT);}
					case -8:
						break;
					case 8:
						{yybegin(YYINITIAL);}
					case -9:
						break;
					case 10:
						{}
					case -10:
						break;
					case 11:
						{counters[0]++;}
					case -11:
						break;
					case 12:
						{counters[2]++;}
					case -12:
						break;
					case 14:
						{}
					case -13:
						break;
					case 15:
						{counters[0]++;}
					case -14:
						break;
					case 17:
						{}
					case -15:
						break;
					case 18:
						{counters[0]++;}
					case -16:
						break;
					case 20:
						{counters[0]++;}
					case -17:
						break;
					case 22:
						{counters[0]++;}
					case -18:
						break;
					case 23:
						{counters[0]++;}
					case -19:
						break;
					case 24:
						{counters[0]++;}
					case -20:
						break;
					case 25:
						{}
					case -21:
						break;
					case 26:
						{counters[0]++;}
					case -22:
						break;
					case 27:
						{counters[0]++;}
					case -23:
						break;
					case 28:
						{counters[0]++;}
					case -24:
						break;
					case 29:
						{counters[0]++;}
					case -25:
						break;
					case 30:
						{counters[0]++;}
					case -26:
						break;
					case 31:
						{counters[0]++;}
					case -27:
						break;
					case 32:
						{counters[0]++;}
					case -28:
						break;
					case 33:
						{counters[0]++;}
					case -29:
						break;
					case 34:
						{counters[0]++;}
					case -30:
						break;
					case 35:
						{counters[0]++;}
					case -31:
						break;
					case 36:
						{counters[0]++;}
					case -32:
						break;
					case 37:
						{counters[0]++;}
					case -33:
						break;
					case 38:
						{counters[0]++;}
					case -34:
						break;
					case 39:
						{counters[0]++;}
					case -35:
						break;
					case 40:
						{counters[0]++;}
					case -36:
						break;
					case 41:
						{counters[0]++;}
					case -37:
						break;
					case 42:
						{counters[0]++;}
					case -38:
						break;
					default:
						yy_error(YY_E_INTERNAL,false);
					case -1:
					}
					yy_initial = true;
					yy_state = yy_state_dtrans[yy_lexical_state];
					yy_next_state = YY_NO_STATE;
					yy_last_accept_state = YY_NO_STATE;
					yy_mark_start();
					yy_this_accept = yy_acpt[yy_state];
					if (YY_NOT_ACCEPT != yy_this_accept) {
						yy_last_accept_state = yy_state;
						yy_mark_end();
					}
				}
			}
		}
	}
}
