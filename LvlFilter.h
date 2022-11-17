class LvlFilter{
        public:        
        LvlFilter();
        void updateArray(bool isGrav, bool isAngle, bool isVelX, bool isVelY, bool isSpeed);

        bool* getFilters();
        private:
        bool filters[5];
};