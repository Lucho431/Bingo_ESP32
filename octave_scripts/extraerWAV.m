function extraerWAV(fileWav)

  audioLenght = size(fileWav);

  if (audioLenght(2) < 1)
    printf("ERROR: no se encuentra el archivo.");
    return
  endif
  extensionWav = fileWav(audioLenght(2) - 2 : audioLenght(2));

  if (extensionWav(1) != 'w' && extensionWav(1) != 'W')
    printf("ERROR: el archivo no es wav.\n");
    return
  endif

  if (extensionWav(2) != 'a' && extensionWav(1) != 'A')
    printf("ERROR: el archivo no es wav.\n");
    return
  endif

  if (extensionWav(3) != 'v' && extensionWav(1) != 'V')
    printf("ERROR: el archivo no es wav.\n");
    return
  endif

  audioReadWav = audioread(fileWav);
  audioReadWav (:, 2) = []; #Elimina la segunda columna de datos
  offset = min(audioReadWav);
  audioOffset = audioReadWav - offset; #Elimina el offset
  valorNorm = max(audioOffset);
  audioNorm = audioOffset / valorNorm; #Normaliza el vector
  audio255 = audioNorm * 255;
  audio8bits = round(audio255);

  audioLenght = size(audio8bits);

  vectorSalida = ones (1, audioLenght(1));
  for i=1:audioLenght(1)
    vectorSalida(i) = audio8bits(i);
  endfor

  file_id = fopen('outWav.txt', 'w');

  fprintf(file_id, "const uint8_t noventa[] = { ");

  renglon = 0;
  for i = 1:audioLenght(1)
    fprintf(file_id, "%i, ", vectorSalida(i));
    renglon = renglon + 1;
    if ( renglon > 35)
      fprintf(file_id, "\n");
      renglon = 0;
    endif
  endfor

  fprintf(file_id, "};");

  fclose(file_id);

endfunction
