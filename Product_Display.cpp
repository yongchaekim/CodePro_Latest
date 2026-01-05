int CalLargestBlock(int id_ignore){
	
	int ID_Remove[MAXN+10];
	int cnt=0;
	for(int i=1; i < N; i++) {
		if(ID[i] != id_ignore) {
			ID_Remove[cnt++] = ID[i];
		}
	}
	int max_block_size = 0;
	int cur_size = 1;
	for (int i = 1; i < cnt; i++){
		if (ID_Remove[i] == ID_Remove[i - 1]) cur_size++;
		else cur_size = 1;
		
		if (max_block_size < cur_size) {
			max_block_size = cur_size;
		}
	}
	return max_block_size;
}
