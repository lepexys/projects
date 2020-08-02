using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Number6
{
    class Translator
    {
        Dictionary<string, List<string>> eng_rus;
        Dictionary<string, List<string>> rus_eng;
        public Translator()
        {
            eng_rus = new Dictionary<string, List<string>>();
            rus_eng = new Dictionary<string, List<string>>();
        }
        public void Add(string word, string translation)
        {
            word = word.Trim();
            word = word.ToLower();
            translation = translation.Trim();
            translation = translation.ToLower();
            bool eng = false;
            if (((word[0] >= 'a') && (word[0] <= 'z')) || ((word[0] >= 'A') && (word[0] <= 'Z'))) eng = true;
            if (eng)
            {
                if (eng_rus.Keys.Contains(word))
                {
                    if (!eng_rus[word].Contains(translation))
                        eng_rus[word].Add(translation);
                }
                else
                {
                    eng_rus.Add(word, new List<string>());
                    eng_rus[word].Add(translation);
                }
                if (rus_eng.Keys.Contains(translation))
                {
                    if (!rus_eng[translation].Contains(word))
                        rus_eng[translation].Add(word);
                }
                else
                {
                    rus_eng.Add(translation, new List<string>());
                    rus_eng[translation].Add(word);
                }
            }
            else
            {
                if (rus_eng.Keys.Contains(word))
                {
                    if (!rus_eng[word].Contains(translation))
                        rus_eng[word].Add(translation);
                }
                else
                {
                    rus_eng.Add(word, new List<string>());
                    rus_eng[word].Add(translation);
                }
                if (eng_rus.Keys.Contains(translation))
                {
                    if (!eng_rus[translation].Contains(word))
                        eng_rus[translation].Add(word);
                }
                else
                {
                    eng_rus.Add(translation, new List<string>());
                    eng_rus[translation].Add(word);
                }
            }
        }
        public List<string> GetTranslations(string word)
        {
            word = word.Trim();
            word = word.ToLower();
            bool eng = false;
            if (((word[0] >= 'a') && (word[0] <= 'z')) || ((word[0] >= 'A') && (word[0] <= 'Z'))) eng = true;
            if (eng)
            {
                if (eng_rus.Keys.Contains(word))
                {
                    return eng_rus[word];
                }
            }
            else
                if (rus_eng.Keys.Contains(word)) 
                {
                return rus_eng[word];
                }
            throw new Exception("Нет такого слова в словаре");
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Translator diction = new Translator();
            bool k = true;
            string word;
            string tran;
            while (k)
            {
                Console.WriteLine("0 - Добавить новый перевод, 1 - Найти перевод, Любое другое - выйти");
                Console.Write("Ваш выбор: ");
                switch (Console.ReadLine())
                {
                    case "0":
                        {
                            Console.Write("Введите слово: ");
                            word = Console.ReadLine();
                            Console.Write("Введите перевод: ");
                            tran = Console.ReadLine();
                            diction.Add(word, tran);
                            break;
                        }
                    case "1":
                        {
                            Console.Write("Введите слово: ");
                            word = Console.ReadLine();
                            try
                            {
                                Console.WriteLine("Переводы: ");
                                foreach (string a in diction.GetTranslations(word))
                                    Console.WriteLine(a);
                            }
                            catch(Exception e)
                            { Console.WriteLine(e.Message); }
                            break;
                        }
                    default: { k = false; break; }
                }
            }
        }
    }
}
